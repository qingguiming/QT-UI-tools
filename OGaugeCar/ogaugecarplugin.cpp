#include "ogaugecar.h"
#include "ogaugecarplugin.h"

#include <QtPlugin>

OGaugeCarPlugin::OGaugeCarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OGaugeCarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OGaugeCarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OGaugeCarPlugin::createWidget(QWidget *parent)
{
    return new OGaugeCar(parent);
}

QString OGaugeCarPlugin::name() const
{
    return QLatin1String("OGaugeCar");
}

QString OGaugeCarPlugin::group() const
{
    return QLatin1String("");
}

QIcon OGaugeCarPlugin::icon() const
{
    return QIcon();
}

QString OGaugeCarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OGaugeCarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OGaugeCarPlugin::isContainer() const
{
    return false;
}

QString OGaugeCarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OGaugeCar\" name=\"oGaugeCar\">\n</widget>\n");
}

QString OGaugeCarPlugin::includeFile() const
{
    return QLatin1String("ogaugecar.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ogaugecarplugin, OGaugeCarPlugin)
#endif // QT_VERSION < 0x050000
