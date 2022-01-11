#include "oadswidget.h"
#include "oadswidgetplugin.h"

#include <QtPlugin>

OAdsWidgetPlugin::OAdsWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OAdsWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OAdsWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OAdsWidgetPlugin::createWidget(QWidget *parent)
{
    return new OAdsWidget(parent);
}

QString OAdsWidgetPlugin::name() const
{
    return QLatin1String("OAdsWidget");
}

QString OAdsWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OAdsWidgetPlugin::icon() const
{
    return QIcon();
}

QString OAdsWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OAdsWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OAdsWidgetPlugin::isContainer() const
{
    return false;
}

QString OAdsWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OAdsWidget\" name=\"oAdsWidget\">\n</widget>\n");
}

QString OAdsWidgetPlugin::includeFile() const
{
    return QLatin1String("oadswidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oadswidgetplugin, OAdsWidgetPlugin)
#endif // QT_VERSION < 0x050000
