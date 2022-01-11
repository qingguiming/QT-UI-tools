#include "ogaugepanel.h"
#include "ogaugepanelplugin.h"

#include <QtPlugin>

OGaugePanelPlugin::OGaugePanelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugePanelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugePanelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugePanelPlugin::createWidget(QWidget *parent)
{
    return new OGaugePanel(parent);
}

QString OGaugePanelPlugin::name() const
{
    return QLatin1String("OGaugePanel");
}

QString OGaugePanelPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugePanelPlugin::icon() const
{
    return QIcon();
}

QString OGaugePanelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugePanelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugePanelPlugin::isContainer() const
{
    return false;
}

QString OGaugePanelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugePanel\" name=\"oGaugePanel\">\n</widget>\n");
}

QString OGaugePanelPlugin::includeFile() const
{
    return QLatin1String("ogaugepanel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugepanelplugin, OGaugePanelPlugin)
#endif // QT_VERSION < 0x050000
