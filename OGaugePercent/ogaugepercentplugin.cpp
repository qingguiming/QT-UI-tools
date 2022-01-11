#include "ogaugepercent.h"
#include "ogaugepercentplugin.h"

#include <QtPlugin>

OGaugePercentPlugin::OGaugePercentPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugePercentPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugePercentPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugePercentPlugin::createWidget(QWidget *parent)
{
    return new OGaugePercent(parent);
}

QString OGaugePercentPlugin::name() const
{
    return QLatin1String("OGaugePercent");
}

QString OGaugePercentPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugePercentPlugin::icon() const
{
    return QIcon();
}

QString OGaugePercentPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugePercentPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugePercentPlugin::isContainer() const
{
    return false;
}

QString OGaugePercentPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugePercent\" name=\"oGaugePercent\">\n</widget>\n");
}

QString OGaugePercentPlugin::includeFile() const
{
    return QLatin1String("ogaugepercent.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugepercentplugin, OGaugePercentPlugin)
#endif // QT_VERSION < 0x050000
