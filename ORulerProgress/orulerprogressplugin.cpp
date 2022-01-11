#include "orulerprogress.h"
#include "orulerprogressplugin.h"

#include <QtPlugin>

ORulerProgressPlugin::ORulerProgressPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ORulerProgressPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ORulerProgressPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ORulerProgressPlugin::createWidget(QWidget *parent)
{
    return new ORulerProgress(parent);
}

QString ORulerProgressPlugin::name() const
{
    return QLatin1String("ORulerProgress");
}

QString ORulerProgressPlugin::group() const
{
    return QLatin1String("");
}

QIcon ORulerProgressPlugin::icon() const
{
    return QIcon();
}

QString ORulerProgressPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ORulerProgressPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ORulerProgressPlugin::isContainer() const
{
    return false;
}

QString ORulerProgressPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ORulerProgress\" name=\"oRulerProgress\">\n</widget>\n");
}

QString ORulerProgressPlugin::includeFile() const
{
    return QLatin1String("orulerprogress.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(orulerprogressplugin, ORulerProgressPlugin)
#endif // QT_VERSION < 0x050000
