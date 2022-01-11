#include "owavedouble.h"
#include "owavedoubleplugin.h"

#include <QtPlugin>

OWaveDoublePlugin::OWaveDoublePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWaveDoublePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWaveDoublePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWaveDoublePlugin::createWidget(QWidget *parent)
{
    return new OWaveDouble(parent);
}

QString OWaveDoublePlugin::name() const
{
    return QLatin1String("OWaveDouble");
}

QString OWaveDoublePlugin::group() const
{
    return QLatin1String("");
}

QIcon OWaveDoublePlugin::icon() const
{
    return QIcon();
}

QString OWaveDoublePlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWaveDoublePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWaveDoublePlugin::isContainer() const
{
    return false;
}

QString OWaveDoublePlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWaveDouble\" name=\"oWaveDouble\">\n</widget>\n");
}

QString OWaveDoublePlugin::includeFile() const
{
    return QLatin1String("owavedouble.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owavedoubleplugin, OWaveDoublePlugin)
#endif // QT_VERSION < 0x050000
