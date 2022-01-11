#include "ocustomgraphics.h"
#include "ocustomgraphicsplugin.h"

#include <QtPlugin>

OCustomGraphicsPlugin::OCustomGraphicsPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OCustomGraphicsPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OCustomGraphicsPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OCustomGraphicsPlugin::createWidget(QWidget *parent)
{
    return new OCustomGraphics(parent);
}

QString OCustomGraphicsPlugin::name() const
{
    return QLatin1String("OCustomGraphics");
}

QString OCustomGraphicsPlugin::group() const
{
    return QLatin1String("");
}

QIcon OCustomGraphicsPlugin::icon() const
{
    return QIcon();
}

QString OCustomGraphicsPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OCustomGraphicsPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OCustomGraphicsPlugin::isContainer() const
{
    return false;
}

QString OCustomGraphicsPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OCustomGraphics\" name=\"oCustomGraphics\">\n</widget>\n");
}

QString OCustomGraphicsPlugin::includeFile() const
{
    return QLatin1String("ocustomgraphics.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ocustomgraphicsplugin, OCustomGraphicsPlugin)
#endif // QT_VERSION < 0x050000
