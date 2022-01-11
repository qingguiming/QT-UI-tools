#include "oswitchbutton.h"
#include "oswitchbuttonplugin.h"

#include <QtPlugin>

OSwitchButtonPlugin::OSwitchButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OSwitchButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OSwitchButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OSwitchButtonPlugin::createWidget(QWidget *parent)
{
    return new OSwitchButton(parent);
}

QString OSwitchButtonPlugin::name() const
{
    return QLatin1String("OSwitchButton");
}

QString OSwitchButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon OSwitchButtonPlugin::icon() const
{
    return QIcon();
}

QString OSwitchButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OSwitchButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OSwitchButtonPlugin::isContainer() const
{
    return false;
}

QString OSwitchButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OSwitchButton\" name=\"oSwitchButton\">\n</widget>\n");
}

QString OSwitchButtonPlugin::includeFile() const
{
    return QLatin1String("oswitchbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oswitchbuttonplugin, OSwitchButtonPlugin)
#endif // QT_VERSION < 0x050000
