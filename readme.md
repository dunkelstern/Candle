# Candle

GRBL controller application with G-Code visualizer written in Qt.

Supported functions:
* Controlling GRBL-based cnc-machine via console commands, buttons on form, numpad.
* Monitoring cnc-machine state.
* Loading, editing, saving and sending of G-code files to cnc-machine.
* Visualizing G-code files.

New in this branch:
* Improved plugin interface (plugins can now intercept G-codes before they are sent to the controller)
* Probing plugin to contact-probe all axes and set the tool length offset with a touch sensor
* Manual assisted tool change with automatic TLO probing
* Some fixes to be able to use the thing with a standard Linux filesystem layout (config file location)

# System requirements for running "Candle"

* Windows/Linux x86
* CPU with SSE2 instruction set support
* Graphics card with OpenGL 2.0 support
* 120 MB free storage space

# Build requirements
Qt 5.12.9 or newer version of Qt 5 with MinGW/GCC compiler.

## Ubuntu

In the directory where you have cloned this project run:

```bash
sudo apt install qt5-default libqt5serialport5-dev qttools5-dev-tools qtmultimedia5-dev qttools5-dev qtscript5-dev
qmake -r candle.pro
make all install -j $(nproc)
```

## Archlinux

You will find a `PKGBUILD` file to be used with `makepkg` in `build_scripts/arch`.
You can build and install a package named `candle-experimental` by switching to that directory and running:

```bash
makepkg
sudo pacman -U candle-experimental-*.pkg.tar.*
```

It will complain if dependencies are missing, just install them with `pacman`

## Windows

Install a version of Qt and MingW. An easy way to do this is to install Python, then do the following in the directory where you have cloned this project:

```bash
python -m pip install aqtinstall
python -m aqt install 5.15.2 windows desktop win64_mingw81 -m qtscript -O qt
```

This installs qt in a subdirectory called qt. The compile as follows:

```
qt\mingw64_81\bin\qmake -r candle.pro
make all install
```

# Screenshots

"Candle" main window:
![screenshot](/screenshots/screenshot.png)
