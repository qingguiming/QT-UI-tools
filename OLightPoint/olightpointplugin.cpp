#include "olightpoint.h"
#include "olightpointplugin.h"

#include <QtPlugin>

OLightPointPlugin::OLightPointPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OLightPointPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OLightPointPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OLightPointPlugin::createWidget(QWidget *parent)
{
    return new OLightPoint(parent);
}

QString OLightPointPlugin::name() const
{
    return QLatin1String("OLightPoint");
}

QString OLightPointPlugin::group() const
{
    return QLatin1String("");
}

QIcon OLightPointPlugin::icon() const
{
    return QIcon();
}

QString OLightPointPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OLightPointPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OLightPointPlugin::isContainer() const
{
    return false;
}

QString OLightPointPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OLightPoint\" name=\"oLightPoint\">\n</widget>\n");
}

QString OLightPointPlugin::includeFile() const
{
    return QLatin1String("olightpoint.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(olightpointplugin, OLightPointPlugin)
#endif // QT_VERSION < 0x050000
