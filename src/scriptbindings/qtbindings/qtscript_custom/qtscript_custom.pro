TARGET = qtscript_custom
include(../qtbindingsbase.pri)
QT += widgets gui
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/ $$PWD/../../../designerplugins/customwidgetsplugin

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../designerplugins/customwidgetsplugin/release/ -lcustomwidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../designerplugins/customwidgetsplugin/debug/ -lcustomwidgets
else:unix: LIBS += -L$$OUT_PWD/../../../designerplugins/customwidgetsplugin -lcustomwidgets

include($$GENERATEDCPP/com_trolltech_qt_custom/com_trolltech_qt_custom.pri)
