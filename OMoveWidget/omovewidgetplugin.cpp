#include "omovewidget.h"
#include "omovewidgetplugin.h"

#include <QtPlugin>

OMoveWidgetPlugin::OMoveWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OMoveWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OMoveWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OMoveWidgetPlugin::createWidget(QWidget *parent)
{
    return new OMoveWidget(parent);
}

QString OMoveWidgetPlugin::name() const
{
    return QLatin1String("OMoveWidget");
}

QString OMoveWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OMoveWidgetPlugin::icon() const
{
    return QIcon();
}

QString OMoveWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OMoveWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OMoveWidgetPlugin::isContainer() const
{
    return false;
}

QString OMoveWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OMoveWidget\" name=\"oMoveWidget\">\n</widget>\n");
}

QString OMoveWidgetPlugin::includeFile() const
{
    return QLatin1String("omovewidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(omovewidgetplugin, OMoveWidgetPlugin)
#endif // QT_VERSION < 0x050000
