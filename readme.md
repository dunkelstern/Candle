Candle
-----------
GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

System requirements for running "Candle":
-------------------
* Windows/Linux x86
* CPU with SSE2 instruction set support
* Graphics card with OpenGL 2.0 support
* 120 MB free storage space

Build requirements:
------------------
Qt 5.12.9 or newer version of Qt 5 with MinGW/GCC compiler.

Ubuntu:
======
In the directory where you have cloned this project run:

```
sudo apt install qt5-default libqt5serialport5-dev qttools5-dev-tools qtmultimedia5-dev qttools5-dev qtscript5-dev
qmake -r candle.pro
make all install -j $(nproc)
```

Windows:
=======

Install a version of Qt and MingW. An easy way to do this is to install Python, then do the following in the directory where you have cloned this project:

```
python -m pip install aqtinstall
python -m aqt install 5.15.2 windows desktop win64_mingw81 -m qtscript -O qt
```

This installs qt in a subdirectory called qt. The compile as follows:

```
qt\mingw64_81\bin\qmake -r candle.pro
make all install
```

Downloads:
----------
For GRBL v1.1 firmware

* Windows: [candle_1.1.7.zip](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.zip)
* Linux: [candle_1.1.7.tar.gz](https://github.com/Denvi/Candle/releases/download/v1.1/Candle_1.1.7.tar.gz)

(for GRBL v0.9 and below use Candle 1.0)

"Candle" main window:
![screenshot](/screenshots/screenshot_heightmap_original.png)
