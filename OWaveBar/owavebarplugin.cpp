#include "owavebar.h"
#include "owavebarplugin.h"

#include <QtPlugin>

OWaveBarPlugin::OWaveBarPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWaveBarPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWaveBarPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWaveBarPlugin::createWidget(QWidget *parent)
{
    return new OWaveBar(parent);
}

QString OWaveBarPlugin::name() const
{
    return QLatin1String("OWaveBar");
}

QString OWaveBarPlugin::group() const
{
    return QLatin1String("");
}

QIcon OWaveBarPlugin::icon() const
{
    return QIcon();
}

QString OWaveBarPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWaveBarPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWaveBarPlugin::isContainer() const
{
    return false;
}

QString OWaveBarPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWaveBar\" name=\"oWaveBar\">\n</widget>\n");
}

QString OWaveBarPlugin::includeFile() const
{
    return QLatin1String("owavebar.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owavebarplugin, OWaveBarPlugin)
#endif // QT_VERSION < 0x050000
