#include "ogaugespeed.h"
#include "ogaugespeedplugin.h"

#include <QtPlugin>

OGaugeSpeedPlugin::OGaugeSpeedPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeSpeedPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeSpeedPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeSpeedPlugin::createWidget(QWidget *parent)
{
    return new OGaugeSpeed(parent);
}

QString OGaugeSpeedPlugin::name() const
{
    return QLatin1String("OGaugeSpeed");
}

QString OGaugeSpeedPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeSpeedPlugin::icon() const
{
    return QIcon();
}

QString OGaugeSpeedPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeSpeedPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeSpeedPlugin::isContainer() const
{
    return false;
}

QString OGaugeSpeedPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeSpeed\" name=\"oGaugeSpeed\">\n</widget>\n");
}

QString OGaugeSpeedPlugin::includeFile() const
{
    return QLatin1String("ogaugespeed.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugespeedplugin, OGaugeSpeedPlugin)
#endif // QT_VERSION < 0x050000
