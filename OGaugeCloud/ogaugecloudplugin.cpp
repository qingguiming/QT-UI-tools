#include "ogaugecloud.h"
#include "ogaugecloudplugin.h"

#include <QtPlugin>

OGaugeCloudPlugin::OGaugeCloudPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeCloudPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeCloudPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeCloudPlugin::createWidget(QWidget *parent)
{
    return new OGaugeCloud(parent);
}

QString OGaugeCloudPlugin::name() const
{
    return QLatin1String("OGaugeCloud");
}

QString OGaugeCloudPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeCloudPlugin::icon() const
{
    return QIcon();
}

QString OGaugeCloudPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeCloudPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeCloudPlugin::isContainer() const
{
    return false;
}

QString OGaugeCloudPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeCloud\" name=\"oGaugeCloud\">\n</widget>\n");
}

QString OGaugeCloudPlugin::includeFile() const
{
    return QLatin1String("ogaugecloud.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugecloudplugin, OGaugeCloudPlugin)
#endif // QT_VERSION < 0x050000
