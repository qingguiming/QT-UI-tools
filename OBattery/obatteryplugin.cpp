#include "obattery.h"
#include "obatteryplugin.h"

#include <QtPlugin>

OBatteryPlugin::OBatteryPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OBatteryPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OBatteryPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OBatteryPlugin::createWidget(QWidget *parent)
{
    return new OBattery(parent);
}

QString OBatteryPlugin::name() const
{
    return QLatin1String("OBattery");
}

QString OBatteryPlugin::group() const
{
    return QLatin1String("");
}

QIcon OBatteryPlugin::icon() const
{
    return QIcon();
}

QString OBatteryPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OBatteryPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OBatteryPlugin::isContainer() const
{
    return false;
}

QString OBatteryPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OBattery\" name=\"oBattery\">\n</widget>\n");
}

QString OBatteryPlugin::includeFile() const
{
    return QLatin1String("obattery.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(obatteryplugin, OBatteryPlugin)
#endif // QT_VERSION < 0x050000
