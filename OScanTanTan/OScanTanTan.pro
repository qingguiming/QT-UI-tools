CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(oscantantanplugin)
TEMPLATE    = lib

HEADERS     = oscantantanplugin.h
SOURCES     = oscantantanplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(oscantantan.pri)
