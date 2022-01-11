#include "ogaugecompass.h"
#include "ogaugecompassplugin.h"

#include <QtPlugin>

OGaugeCompassPlugin::OGaugeCompassPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeCompassPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeCompassPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeCompassPlugin::createWidget(QWidget *parent)
{
    return new OGaugeCompass(parent);
}

QString OGaugeCompassPlugin::name() const
{
    return QLatin1String("OGaugeCompass");
}

QString OGaugeCompassPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeCompassPlugin::icon() const
{
    return QIcon();
}

QString OGaugeCompassPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeCompassPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeCompassPlugin::isContainer() const
{
    return false;
}

QString OGaugeCompassPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeCompass\" name=\"oGaugeCompass\">\n</widget>\n");
}

QString OGaugeCompassPlugin::includeFile() const
{
    return QLatin1String("ogaugecompass.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugecompassplugin, OGaugeCompassPlugin)
#endif // QT_VERSION < 0x050000
