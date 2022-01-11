CONFIG      += plugin debug_and_release
TARGET      = $$qtLibraryTarget(olightbuttonplugin)
TEMPLATE    = lib

HEADERS     = olightbuttonplugin.h
SOURCES     = olightbuttonplugin.cpp
RESOURCES   = icons.qrc
LIBS        += -L. 

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS    += target

include(olightbutton.pri)
