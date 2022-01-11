#include "owidget.h"
#include "owidgetplugin.h"

#include <QtPlugin>

OWidgetPlugin::OWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWidgetPlugin::createWidget(QWidget *parent)
{
    return new OWidget(parent);
}

QString OWidgetPlugin::name() const
{
    return QLatin1String("OWidget");
}

QString OWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OWidgetPlugin::icon() const
{
    return QIcon();
}

QString OWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWidgetPlugin::isContainer() const
{
    return false;
}

QString OWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWidget\" name=\"oWidget\">\n</widget>\n");
}

QString OWidgetPlugin::includeFile() const
{
    return QLatin1String("owidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owidgetplugin, OWidgetPlugin)
#endif // QT_VERSION < 0x050000
