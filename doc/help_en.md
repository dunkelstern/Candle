<style type="text/css" rel="stylesheet">
img[src*='#center'] {
    display: block;
    margin: auto;
}
.center {
    text-align: center;
}
table {
    width: 100%;
}
</style>

# Candle

# Contents

[1 What is Candle](#1-what-is-candle)  
[2 Requirements for running Candle](#2-requirements-for-running-candle)  
&nbsp;&nbsp;&nbsp;&nbsp;[2.1 Hardware Requirements](#2-1-hardware-requirements)  
&nbsp;&nbsp;&nbsp;&nbsp;[2.2 Software Requirements](#2-2-software-requirements)  
[3 Running the Application](#3-running-the-application)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.1 Installation](#3-1-installation)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.2 Running](#3-2-running)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.3 Main Window](#3-3-main-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.1 Main Menu](#3-3-1-main-menu)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2 Windows](#3-3-2-windows)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.1 The "G-code program" window](#3-3-2-1-the-g-code-program-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.1 The "Visualizer" window](#3-3-2-2-the-visualizer-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.3 The "Camera" window](#3-3-2-3-the-camera-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.4 The "Console" window](#3-3-2-4-the-console-window)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.2.5 The "Device", "Modification" and "User" windows](#3-3-2-5-the-device-modification-and-user-windows)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3 Toolboxes](#3-3-3-toolboxes)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.1 Status panel](#3-3-3-1-status-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.2 Control panel](#3-3-3-2-control-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.3 Coordinate System panel](#3-3-3-3-coordinate-system-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.4 Spindle Panel](#3-3-3-4-spindle-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.5 Jog panel](#3-3-3-5-jog-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.6 Override panel](#3-3-3-6-override-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.7 Heightmap panel](#3-3-3-7-heightmap-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[3.3.3.8 User commands panel](#3-3-3-8-user-commands-panel)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.4 Settings Window](#3-4-settings-window)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.5 Preparing for running a program](#3-5-preparing-for-running-a-program)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.6 Loading the G-Code program](#3-6-loading-the-g-code-program)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.7 Creating a Height Map](#3-7-creating-a-height-map)  
&nbsp;&nbsp;&nbsp;&nbsp;[3.8 Running a G-Code program](#3-8-running-a-g-code-program)  
[4 Console output](#4-console-output)  
[5 Plugin development](#5-plugin-development)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.1 Config file](#5-1-config-file)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.2 Script file](#5-2-script-file)  
&nbsp;&nbsp;&nbsp;&nbsp;[5.3 Translation file](#5-3-translation-file)  
[Appendix A. Controller settings](#appendix-a-controller-settings)  
[Appendix B. Table of G-code commands](#appendix-b-table-of-g-code-commands)  

----

# 1 What is Candle

The "Candle" program (hereinafter referred to as the program) is designed to control numerically controlled machine tools (hereinafter referred to as CNC) that have a "GRBL" controller (hereinafter referred to as the controller) by means of a PC.

The program allows you to work with milling 3-axis machines and laser cutters.

The main functions of the program:

- Loading, editing, saving control programs (G-Code).
- G-Code visualization.
- Probing the surface to create height-maps and correct the G-Code programm to conform to them.
- G-Code transfer to the machine.
- CNC status display.
- Manual control of the CNC.

# 2 Requirements for running Candle

## 2.1 Hardware Requirements

- CPU with SSE2 instruction set support
- Graphics card with OpenGL 2.0 support
- 120 MB free storage space
- Minimum of 1280x720 display resolution
- USB or RS-232 port to connect to the controller

## 2.2 Software Requirements

- Windows 7 or higher or Linux
- Driver for controller installed
- 3D-Graphics driver installed

# 3 Running the Application

## 3.1 Installation

The program comes as an archive "candle_v.v.v_x86.zip" for 32-bit processors and "candle_v.v.v_x64.zip" for 64-bit ones, where v.v.v is the program version number.

To install you need to unpack the archive to a folder, for example: "D:\Candle". The folder will be the "Candle" program directory with all the files necessary for it to work.

After unpacking, you need to create a shortcut to the executable file "D:\Candle\candle.exe" in order to provide further quick launching.

## 3.2 Running

The program is launched by calling the file "candle.exe" from the installation folder or using the previously created shortcut.

## 3.3 Main Window

When you start the program, the display should show the main program window shown in Figure 1.

![Main Window of Candle](images/en/mainwindow.png#center)
<p class="center">Figure 1 - Main Window</p>

The main window consists of the main menu at the top, a set of windows and tool boxes:

- "G-code program" - the main window, displays the list of commands to run on the CNC.
- "Visualizer" - graphical representation of the G-Code.
- "Camera" - image from the camera if you have one.
- "Console" - the window for sending commands to the "GRBL" CNC controller and displaying responses.
- "Device" - the window with the set of panels for CNC control.
- "Modification" - window with a set of panels for G-Code modification.
- "User" - window with a set of user panels, plugins will appear here too.

Each window has a header area and a content area. The title bar contains the window title, "Separate" and "Close" buttons, the content area contains input and display elements, as well as toolbars.

All windows, except the window "G-code program", can be moved by dragging with pressed left mouse button on the window title bar. As you move, the layout of the main program window will dynamically change, indicating the future location of the moved window.

Windows can be separated from the main window by clicking on the "Separate" header button, closed - "Close". Separated windows can be returned to the main window by dragging the header and closed by selecting the appropriate item in the main menu "View - Windows".

The size of the windows can be changed by clicking on the window border and dragging it to the desired side.

### 3.3.1 Main Menu

### 3.3.2 Windows

#### 3.3.2.1 The "G-code program" window

#### 3.3.2.1 The "Visualizer" window

#### 3.3.2.3 The "Camera" window

#### 3.3.2.4 The "Console" window

#### 3.3.2.5 The "Device", "Modification" and "User" windows

### 3.3.3 Toolboxes

#### 3.3.3.1 Status panel

#### 3.3.3.2 Control panel

#### 3.3.3.3 Coordinate System panel

#### 3.3.3.4 Spindle Panel

#### 3.3.3.5 Jog panel

#### 3.3.3.6 Override panel

#### 3.3.3.7 Heightmap panel

#### 3.3.3.8 User commands panel

## 3.4 Settings Window

## 3.5 Preparing for running a program

## 3.6 Loading the G-Code program

## 3.7 Creating a Height Map

## 3.8 Running a G-Code program

# 4 Console output

# 5 Plugin development

## 5.1 Config file

## 5.2 Script file

## 5.3 Translation file

# Appendix A. Controller settings

# Appendix B. Table of G-code commands