
#include "oshadowclock.h"
#include "oshadowclockplugin.h"

#include <QtPlugin>

OShadowClockPlugin::OShadowClockPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OShadowClockPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OShadowClockPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OShadowClockPlugin::createWidget(QWidget *parent)
{
    return new OShadowClock(parent);
}

QString OShadowClockPlugin::name() const
{
    return QLatin1String("OShadowClock");
}

QString OShadowClockPlugin::group() const
{
    return QLatin1String("");
}

QIcon OShadowClockPlugin::icon() const
{
    return QIcon();
}

QString OShadowClockPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OShadowClockPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OShadowClockPlugin::isContainer() const
{
    return false;
}

QString OShadowClockPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OShadowClock\" name=\"oShadowClock\">\n</widget>\n");
}

QString OShadowClockPlugin::includeFile() const
{
    return QLatin1String("oshadowclock.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oshadowclockplugin, OShadowClockPlugin)
#endif // QT_VERSION < 0x050000
