CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(otimeaxiswidgetplugin)
TEMPLATE    = lib

HEADERS     = otimeaxiswidgetplugin.h
SOURCES     = otimeaxiswidgetplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(otimeaxiswidget.pri)
