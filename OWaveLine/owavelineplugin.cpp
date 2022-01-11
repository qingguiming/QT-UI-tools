#include "owaveline.h"
#include "owavelineplugin.h"

#include <QtPlugin>

OWaveLinePlugin::OWaveLinePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWaveLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWaveLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWaveLinePlugin::createWidget(QWidget *parent)
{
    return new OWaveLine(parent);
}

QString OWaveLinePlugin::name() const
{
    return QLatin1String("OWaveLine");
}

QString OWaveLinePlugin::group() const
{
    return QLatin1String("");
}

QIcon OWaveLinePlugin::icon() const
{
    return QIcon();
}

QString OWaveLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWaveLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWaveLinePlugin::isContainer() const
{
    return false;
}

QString OWaveLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWaveLine\" name=\"oWaveLine\">\n</widget>\n");
}

QString OWaveLinePlugin::includeFile() const
{
    return QLatin1String("owaveline.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owavelineplugin, OWaveLinePlugin)
#endif // QT_VERSION < 0x050000
