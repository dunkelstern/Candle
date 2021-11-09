TEMPLATE = subdirs
 
SUBDIRS = cameraplugin customwidgetsplugin

install_cameraplugin.path = ../../bin/plugins/camera/plugins
install_cameraplugin.files = cameraplugin/release/cameraplugin.dll

install_customwidgetsplugin.path = ../../bin

win32:CONFIG(release, debug|release): install_customwidgetsplugin.files = customwidgetsplugin/release/libcustomwidgets.so
else:win32:CONFIG(debug, debug|release): install_customwidgetsplugin.files = customwidgetsplugin/debug/libcustomwidgets.so
else:unix: install_customwidgetsplugin.files = customwidgetsplugin/libcustomwidgets.so

INSTALLS += install_cameraplugin install_customwidgetsplugin
