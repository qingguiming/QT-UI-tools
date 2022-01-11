#include "ogaugeedit.h"
#include "ogaugeeditplugin.h"

#include <QtPlugin>

OGaugeEditPlugin::OGaugeEditPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeEditPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeEditPlugin::createWidget(QWidget *parent)
{
    return new OGaugeEdit(parent);
}

QString OGaugeEditPlugin::name() const
{
    return QLatin1String("OGaugeEdit");
}

QString OGaugeEditPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeEditPlugin::icon() const
{
    return QIcon();
}

QString OGaugeEditPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeEditPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeEditPlugin::isContainer() const
{
    return false;
}

QString OGaugeEditPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeEdit\" name=\"oGaugeEdit\">\n</widget>\n");
}

QString OGaugeEditPlugin::includeFile() const
{
    return QLatin1String("ogaugeedit.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugeeditplugin, OGaugeEditPlugin)
#endif // QT_VERSION < 0x050000
