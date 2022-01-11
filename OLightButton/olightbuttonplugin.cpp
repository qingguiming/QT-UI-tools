#include "olightbutton.h"
#include "olightbuttonplugin.h"

#include <QtPlugin>

OLightButtonPlugin::OLightButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OLightButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OLightButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OLightButtonPlugin::createWidget(QWidget *parent)
{
    return new OLightButton(parent);
}

QString OLightButtonPlugin::name() const
{
    return QLatin1String("OLightButton");
}

QString OLightButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon OLightButtonPlugin::icon() const
{
    return QIcon();
}

QString OLightButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OLightButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OLightButtonPlugin::isContainer() const
{
    return false;
}

QString OLightButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OLightButton\" name=\"oLightButton\">\n</widget>\n");
}

QString OLightButtonPlugin::includeFile() const
{
    return QLatin1String("olightbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(olightbuttonplugin, OLightButtonPlugin)
#endif // QT_VERSION < 0x050000
