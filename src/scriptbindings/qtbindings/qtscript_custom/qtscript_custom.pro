TARGET = qtscript_custom
include(../qtbindingsbase.pri)
QT += widgets gui
SOURCES += plugin.cpp
HEADERS += plugin.h
INCLUDEPATH += ./include/ $$PWD/../../../designerplugins/customwidgetsplugin
LIBS += -L$$OUT_PWD/../../../designerplugins/customwidgetsplugin -lcustomwidgets
include($$GENERATEDCPP/com_trolltech_qt_custom/com_trolltech_qt_custom.pri)
