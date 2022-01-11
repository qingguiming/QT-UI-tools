#include "owaveplot.h"
#include "owaveplotplugin.h"

#include <QtPlugin>

OWavePlotPlugin::OWavePlotPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OWavePlotPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OWavePlotPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OWavePlotPlugin::createWidget(QWidget *parent)
{
    return new OWavePlot(parent);
}

QString OWavePlotPlugin::name() const
{
    return QLatin1String("OWavePlot");
}

QString OWavePlotPlugin::group() const
{
    return QLatin1String("");
}

QIcon OWavePlotPlugin::icon() const
{
    return QIcon();
}

QString OWavePlotPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OWavePlotPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OWavePlotPlugin::isContainer() const
{
    return false;
}

QString OWavePlotPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OWavePlot\" name=\"oWavePlot\">\n</widget>\n");
}

QString OWavePlotPlugin::includeFile() const
{
    return QLatin1String("owaveplot.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(owaveplotplugin, OWavePlotPlugin)
#endif // QT_VERSION < 0x050000
