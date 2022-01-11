#-------------------------------------------------
#
# Project created by QtCreator 2021-12-25T15:15:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PluginDemo
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/include
LIBS += $$PWD/lib/ocomboboxplugin.lib
LIBS += $$PWD/lib/oscantantanplugin.lib
LIBS += $$PWD/lib/owidgetplugin.lib
LIBS += $$PWD/lib/omovewidgetplugin.lib
LIBS += $$PWD/lib/oaudiowavewidgetplugin.lib
LIBS += $$PWD/lib/owavebarplugin.lib
LIBS += $$PWD/lib/owavedoubleplugin.lib
LIBS += $$PWD/lib/owavelineplugin.lib
LIBS += $$PWD/lib/owaveplotplugin.lib
LIBS += $$PWD/lib/otimeaxiswidgetplugin.lib
LIBS += $$PWD/lib/ogaugeclockplugin.lib
LIBS += $$PWD/lib/owavewaterplugin.lib
LIBS += $$PWD/lib/ogaugecloudplugin.lib
LIBS += $$PWD/lib/oshadowcalendarplugin.lib
LIBS += $$PWD/lib/oshadowclockplugin.lib
LIBS += $$PWD/lib/ogaugeeditplugin.lib
LIBS += $$PWD/lib/ocustomgraphicsplugin.lib
LIBS += $$PWD/lib/ogaugecompassplugin.lib
LIBS += $$PWD/lib/orulertempplugin.lib
LIBS += $$PWD/lib/ogaugespeedplugin.lib
LIBS += $$PWD/lib/orulerprogressplugin.lib
LIBS += $$PWD/lib/oswitchbuttonplugin.lib
LIBS += $$PWD/lib/oanimationbuttonplugin.lib
LIBS += $$PWD/lib/ogaugecarplugin.lib
LIBS += $$PWD/lib/ogaugepercentplugin.lib
LIBS += $$PWD/lib/oprogressringplugin.lib
LIBS += $$PWD/lib/ocustompieplugin.lib
LIBS += $$PWD/lib/oantlineplugin.lib
LIBS += $$PWD/lib/oadswidgetplugin.lib
LIBS += $$PWD/lib/otiledbgplugin.lib
LIBS += $$PWD/lib/ocolorbuttonplugin.lib
LIBS += $$PWD/lib/ogaugepanelplugin.lib
LIBS += $$PWD/lib/oimageanimationplugin.lib
LIBS += $$PWD/lib/olightpointplugin.lib
LIBS += $$PWD/lib/olightbuttonplugin.lib
LIBS += $$PWD/lib/onavlabelplugin.lib

LIBS += $$PWD/lib/obatteryplugin.lib



















SOURCES += main.cpp\
        mainwindow.cpp \
    mywidget.cpp

HEADERS  += mainwindow.h \
    mywidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
