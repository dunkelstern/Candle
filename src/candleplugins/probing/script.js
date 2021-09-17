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
var deviceState = -1;
var senderState = -1;
var tlo = 0;

// Ui
var uiPanel;
var uiSettings;

function init()
{
    loader.setWorkingDirectory(new QDir(pluginPath));
    loader.addPluginPath(appPath);

    app.deviceStateChanged.connect(onAppDeviceStateChanged);
    app.senderStateChanged.connect(onAppSenderStateChanged);
    app.responseReceived.connect(onAppResponseReceived);
    app.settingsLoaded.connect(onAppSettingsLoaded);
}

function onProbeToolClicked(toolName) {
    return function() {
        // Switch to Tool length offset mode
        tlo = 1;

        // start tlo probing, stop spindle, move to position
        app.sendCommand("M5");
        app.sendCommand("G53 G0 Z0"); // clear part, move to top
        app.sendCommand("G30");       // move to toolchange position

        // Reset TLO
        app.sendCommand("G49");

        // Run probe
        app.sendCommand("G38.2 F180 Z-100");
    };
}

function createPanelWidget() {
    var f = new QFile(pluginPath + "/widget.ui");

    function onProbeClicked(a) {
        return function() {
            app.sendCommand("".concat("G38.2 F180 ", a));
        }
    }

    if (f.open(QIODevice.ReadOnly)) {
        uiPanel = loader.load(f);

        uiPanel.cmdProbeXP.clicked.connect(onProbeClicked("X100"));
        uiPanel.cmdProbeXN.clicked.connect(onProbeClicked("X-100"));
        uiPanel.cmdProbeYP.clicked.connect(onProbeClicked("Y100"));
        uiPanel.cmdProbeYN.clicked.connect(onProbeClicked("Y-100"));
        uiPanel.cmdProbeZ.clicked.connect(onProbeClicked("Z-100"));
        uiPanel.cmdProbeTool.clicked.connect(onProbeToolClicked(false));
    }
    return uiPanel;
}

function onAppSettingsLoaded() {
    var u = app.settings.units;
    var b = u ? 999 : 9999;

    uiPanel.txtProbeX.decimals = u ? 4 : 3;
    uiPanel.txtProbeY.decimals = u ? 4 : 3;
    uiPanel.txtProbeZ.decimals = u ? 4 : 3;

    uiPanel.txtProbeX.mimimum = -b;
    uiPanel.txtProbeX.maximum = b;
    uiPanel.txtProbeY.mimimum = -b;
    uiPanel.txtProbeY.maximum = b;
    uiPanel.txtProbeZ.mimimum = -b;
    uiPanel.txtProbeZ.maximum = b;
}

function onAppDeviceStateChanged(status) {
    uiPanel.setEnabled(
        ((senderState == 4) || (senderState == 2))
        && (status == 1)
    );
    deviceState = status;
}

function onAppSenderStateChanged(status) {
    uiPanel.setEnabled(
        ((status == 4) || (status == 2))
        && (deviceState == 1)
    );
    senderState = status;
}

function onAppResponseReceived(command, index, response) {
    // Record Probe results and step into next probing cycle if requested
    var G38 = new RegExp("G38\.2.*");
    var s = command.match(G38);
    if (s) {
        var prb = new RegExp(".*PRB:([^,]*),([^,]*),([^\\]^\\:]*).*");
        s = response.match(prb)
        if (s) {
            // display probe result
            uiPanel.txtProbeX.value = parseFloat(s[1]);
            uiPanel.txtProbeY.value = parseFloat(s[2]);
            uiPanel.txtProbeZ.value = parseFloat(s[3]);

            // if in toolchange mode run the appropriate steps
            var probeZ = parseFloat(s[3]);
            if (tlo == 1) {
                // tlo = 1 -> run another probe cycle but slower
                app.sendCommand("G91");
                app.sendCommand("G0 Z1");
                app.sendCommand("G38.2 F10 Z-2");
                tlo = 2;
            } else if (tlo == 2) {
                // tlo = 2 -> We have the probing result, calculate and set TLO
                app.sendCommand("G90");
                var z = (probeZ + 50);
                app.sendCommand("G43.1 Z" + z.toFixed(3).toString());
                app.sendCommand("G53 G0 Z0");
                app.sendCommand("G53 G0 X0 Y0");

                // Exit toolchange mode
                tlo = 0;
            }
        }
    }
}
