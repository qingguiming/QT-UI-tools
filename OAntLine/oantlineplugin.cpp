#include "oantline.h"
#include "oantlineplugin.h"

#include <QtPlugin>

OAntLinePlugin::OAntLinePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OAntLinePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OAntLinePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OAntLinePlugin::createWidget(QWidget *parent)
{
    return new OAntLine(parent);
}

QString OAntLinePlugin::name() const
{
    return QLatin1String("OAntLine");
}

QString OAntLinePlugin::group() const
{
    return QLatin1String("");
}

QIcon OAntLinePlugin::icon() const
{
    return QIcon();
}

QString OAntLinePlugin::toolTip() const
{
    return QLatin1String("");
}

QString OAntLinePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OAntLinePlugin::isContainer() const
{
    return false;
}

QString OAntLinePlugin::domXml() const
{
    return QLatin1String("<widget class=\"OAntLine\" name=\"oAntLine\">\n</widget>\n");
}

QString OAntLinePlugin::includeFile() const
{
    return QLatin1String("oantline.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oantlineplugin, OAntLinePlugin)
#endif // QT_VERSION < 0x050000
