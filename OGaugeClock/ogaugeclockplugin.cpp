#include "ogaugeclock.h"
#include "ogaugeclockplugin.h"

#include <QtPlugin>

OGaugeClockPlugin::OGaugeClockPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeClockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeClockPlugin::createWidget(QWidget *parent)
{
    return new OGaugeClock(parent);
}

QString OGaugeClockPlugin::name() const
{
    return QLatin1String("OGaugeClock");
}

QString OGaugeClockPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeClockPlugin::icon() const
{
    return QIcon();
}

QString OGaugeClockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeClockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeClockPlugin::isContainer() const
{
    return false;
}

QString OGaugeClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeClock\" name=\"oGaugeClock\">\n</widget>\n");
}

QString OGaugeClockPlugin::includeFile() const
{
    return QLatin1String("ogaugeclock.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugeclockplugin, OGaugeClockPlugin)
#endif // QT_VERSION < 0x050000
