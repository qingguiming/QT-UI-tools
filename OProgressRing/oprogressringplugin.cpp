#include "oprogressring.h"
#include "oprogressringplugin.h"

#include <QtPlugin>

OProgressRingPlugin::OProgressRingPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OProgressRingPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OProgressRingPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OProgressRingPlugin::createWidget(QWidget *parent)
{
    return new OProgressRing(parent);
}

QString OProgressRingPlugin::name() const
{
    return QLatin1String("OProgressRing");
}

QString OProgressRingPlugin::group() const
{
    return QLatin1String("");
}

QIcon OProgressRingPlugin::icon() const
{
    return QIcon();
}

QString OProgressRingPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OProgressRingPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OProgressRingPlugin::isContainer() const
{
    return false;
}

QString OProgressRingPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OProgressRing\" name=\"oProgressRing\">\n</widget>\n");
}

QString OProgressRingPlugin::includeFile() const
{
    return QLatin1String("oprogressring.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oprogressringplugin, OProgressRingPlugin)
#endif // QT_VERSION < 0x050000
