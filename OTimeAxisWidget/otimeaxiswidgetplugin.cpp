#include "otimeaxiswidget.h"
#include "otimeaxiswidgetplugin.h"

#include <QtPlugin>

OTimeAxisWidgetPlugin::OTimeAxisWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OTimeAxisWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OTimeAxisWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OTimeAxisWidgetPlugin::createWidget(QWidget *parent)
{
    return new OTimeAxisWidget(parent);
}

QString OTimeAxisWidgetPlugin::name() const
{
    return QLatin1String("OTimeAxisWidget");
}

QString OTimeAxisWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OTimeAxisWidgetPlugin::icon() const
{
    return QIcon();
}

QString OTimeAxisWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OTimeAxisWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OTimeAxisWidgetPlugin::isContainer() const
{
    return false;
}

QString OTimeAxisWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OTimeAxisWidget\" name=\"oTimeAxisWidget\">\n</widget>\n");
}

QString OTimeAxisWidgetPlugin::includeFile() const
{
    return QLatin1String("otimeaxiswidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(otimeaxiswidgetplugin, OTimeAxisWidgetPlugin)
#endif // QT_VERSION < 0x050000
