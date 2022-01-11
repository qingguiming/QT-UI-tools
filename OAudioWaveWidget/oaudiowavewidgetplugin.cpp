#include "oaudiowavewidget.h"
#include "oaudiowavewidgetplugin.h"

#include <QtPlugin>

OAudioWaveWidgetPlugin::OAudioWaveWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OAudioWaveWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OAudioWaveWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OAudioWaveWidgetPlugin::createWidget(QWidget *parent)
{
    return new OAudioWaveWidget(parent);
}

QString OAudioWaveWidgetPlugin::name() const
{
    return QLatin1String("OAudioWaveWidget");
}

QString OAudioWaveWidgetPlugin::group() const
{
    return QLatin1String("");
}

QIcon OAudioWaveWidgetPlugin::icon() const
{
    return QIcon();
}

QString OAudioWaveWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OAudioWaveWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OAudioWaveWidgetPlugin::isContainer() const
{
    return false;
}

QString OAudioWaveWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OAudioWaveWidget\" name=\"oAudioWaveWidget\">\n</widget>\n");
}

QString OAudioWaveWidgetPlugin::includeFile() const
{
    return QLatin1String("oaudiowavewidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oaudiowavewidgetplugin, OAudioWaveWidgetPlugin)
#endif // QT_VERSION < 0x050000
