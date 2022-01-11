#include "oshadowcalendar.h"
#include "oshadowcalendarplugin.h"

#include <QtPlugin>

OShadowCalendarPlugin::OShadowCalendarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OShadowCalendarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OShadowCalendarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OShadowCalendarPlugin::createWidget(QWidget *parent)
{
    return new OShadowCalendar(parent);
}

QString OShadowCalendarPlugin::name() const
{
    return QLatin1String("OShadowCalendar");
}

QString OShadowCalendarPlugin::group() const
{
    return QLatin1String("");
}

QIcon OShadowCalendarPlugin::icon() const
{
    return QIcon();
}

QString OShadowCalendarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OShadowCalendarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OShadowCalendarPlugin::isContainer() const
{
    return false;
}

QString OShadowCalendarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OShadowCalendar\" name=\"oShadowCalendar\">\n</widget>\n");
}

QString OShadowCalendarPlugin::includeFile() const
{
    return QLatin1String("oshadowcalendar.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oshadowcalendarplugin, OShadowCalendarPlugin)
#endif // QT_VERSION < 0x050000
