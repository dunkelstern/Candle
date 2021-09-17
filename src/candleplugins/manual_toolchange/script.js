script.importExtension("qt.core");
script.importExtension("qt.gui");
script.importExtension("qt.widgets");
script.importExtension("qt.custom");
script.importExtension("qt.uitools");

// TODO:
// - Configuration:
//   - TLO sensor position (G28, G30 or custom)
//   - Max probing length, defaults to 100mm currently
//   - Probing speeds (first and slower secondary)
//   - Max Z-Axis travel above TLO sensor

// Vars
var appPath = app.path;
var pluginPath = script.path;
var loader = new QUiLoader();
var settings = new QSettings(pluginPath + "/settings.ini", QSettings.IniFormat);
var toolChange = 0;
var spindleSpeed = 0;
var spindleEnabled = false;

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);

    app.responseReceived.connect(onAppResponseReceived);
}

function startToolChange(toolName) {
    // Switch to toolchange mode
    toolChange = 1;

    // start toolchange, stop spindle, move to position
    app.sendCommand("M5");
    app.sendCommand("G53 G0 Z0"); // clear part, move to top
    app.sendCommand("G30");       // move to toolchange position

    // Wait for user to change tool
    app.displayMessageBox(1, "Tool change", "Please change tool and press ok for probing cycle!\nChange to: " + toolName, 1024);

    // Reset TLO
    app.sendCommand("G49");

    // Run probe
    app.sendCommand("G38.2 F180 Z-100");
}

function preprocessCommand(command) {
    var M6 = new RegExp("M0?6 ?(.*)");
    var s = command.match(M6)
    if (s) {
        print("Toolchange detected, halting sender");
        app.setSenderState(2); // Pause
        startToolChange(s[1]); // run toolchange and wait for user input
        return '';
    }
    return command;
}

function onAppResponseReceived(command, index, response) {
    // Record Probe results and step into next probing cycle if requested
    var G38 = new RegExp("G38\.2.*");
    var s = command.match(G38);
    if (s) {
        var prb = new RegExp(".*PRB:([^,]*),([^,]*),([^\\]^\\:]*).*");
        s = response.match(prb)
        if (s) {
            // if in toolchange mode run the appropriate steps
            var probeZ = parseFloat(s[3]);
            if (toolChange == 1) {
                // toolChange = 1 -> run another probe cycle but slower
                app.sendCommand("G91");
                app.sendCommand("G0 Z1");
                app.sendCommand("G38.2 F10 Z-2");
                toolChange = 2;
            } else if (toolChange == 2) {
                // toolChange = 2 -> We have the probing result, calculate and set TLO
                app.sendCommand("G90");
                var z = (probeZ + 50);
                app.sendCommand("G43.1 Z" + z.toFixed(3).toString());
                app.sendCommand("G53 G0 Z0");
                app.sendCommand("G53 G0 X0 Y0");

                // Restore spindle speed
                if (spindleEnabled) {
                    app.sendCommand("S" + spindleSpeed.toString());
                }
                // Exit toolchange mode
                toolChange = 0;
            }
        }
    }

    // Record spindle speeds
    var M5 = new RegExp(".*M0?5.*");
    s = command.match(M5);
    if (s && toolChange == 0) {
        spindleEnabled = false;
        spindleSpeed = 0;
    }

    var M3 = new RegExp(".*M0?3 S([0-9]+).*");
    s = command.match(M3);
    if (s) {
        if (parseFloat(s[1]) > 0) {
            spindleEnabled = true;
            spindleSpeed = parseFloat(s[1]);
        }
    }
}
