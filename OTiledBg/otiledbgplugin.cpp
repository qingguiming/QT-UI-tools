#include "otiledbg.h"
#include "otiledbgplugin.h"

#include <QtPlugin>

OTiledBgPlugin::OTiledBgPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OTiledBgPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OTiledBgPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OTiledBgPlugin::createWidget(QWidget *parent)
{
    return new OTiledBg(parent);
}

QString OTiledBgPlugin::name() const
{
    return QLatin1String("OTiledBg");
}

QString OTiledBgPlugin::group() const
{
    return QLatin1String("");
}

QIcon OTiledBgPlugin::icon() const
{
    return QIcon();
}

QString OTiledBgPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OTiledBgPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OTiledBgPlugin::isContainer() const
{
    return false;
}

QString OTiledBgPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OTiledBg\" name=\"oTiledBg\">\n</widget>\n");
}

QString OTiledBgPlugin::includeFile() const
{
    return QLatin1String("otiledbg.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(otiledbgplugin, OTiledBgPlugin)
#endif // QT_VERSION < 0x050000
