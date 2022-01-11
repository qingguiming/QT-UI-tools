#include "owavewater.h"
#include "owavewaterplugin.h"

#include <QtPlugin>

OWaveWaterPlugin::OWaveWaterPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWaveWaterPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWaveWaterPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWaveWaterPlugin::createWidget(QWidget *parent)
{
    return new OWaveWater(parent);
}

QString OWaveWaterPlugin::name() const
{
    return QLatin1String("OWaveWater");
}

QString OWaveWaterPlugin::group() const
{
    return QLatin1String("");
}

QIcon OWaveWaterPlugin::icon() const
{
    return QIcon();
}

QString OWaveWaterPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWaveWaterPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWaveWaterPlugin::isContainer() const
{
    return false;
}

QString OWaveWaterPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWaveWater\" name=\"oWaveWater\">\n</widget>\n");
}

QString OWaveWaterPlugin::includeFile() const
{
    return QLatin1String("owavewater.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owavewaterplugin, OWaveWaterPlugin)
#endif // QT_VERSION < 0x050000
