#include "ocolorbutton.h"
#include "ocolorbuttonplugin.h"

#include <QtPlugin>

OColorButtonPlugin::OColorButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OColorButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OColorButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OColorButtonPlugin::createWidget(QWidget *parent)
{
    return new OColorButton(parent);
}

QString OColorButtonPlugin::name() const
{
    return QLatin1String("OColorButton");
}

QString OColorButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon OColorButtonPlugin::icon() const
{
    return QIcon();
}

QString OColorButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OColorButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OColorButtonPlugin::isContainer() const
{
    return false;
}

QString OColorButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OColorButton\" name=\"oColorButton\">\n</widget>\n");
}

QString OColorButtonPlugin::includeFile() const
{
    return QLatin1String("ocolorbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ocolorbuttonplugin, OColorButtonPlugin)
#endif // QT_VERSION < 0x050000
