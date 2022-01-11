#include "oscantantan.h"
#include "oscantantanplugin.h"

#include <QtPlugin>

OScanTanTanPlugin::OScanTanTanPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OScanTanTanPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OScanTanTanPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OScanTanTanPlugin::createWidget(QWidget *parent)
{
    return new OScanTanTan(parent);
}

QString OScanTanTanPlugin::name() const
{
    return QLatin1String("OScanTanTan");
}

QString OScanTanTanPlugin::group() const
{
    return QLatin1String("");
}

QIcon OScanTanTanPlugin::icon() const
{
    return QIcon();
}

QString OScanTanTanPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OScanTanTanPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OScanTanTanPlugin::isContainer() const
{
    return false;
}

QString OScanTanTanPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OScanTanTan\" name=\"oScanTanTan\">\n</widget>\n");
}

QString OScanTanTanPlugin::includeFile() const
{
    return QLatin1String("oscantantan.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oscantantanplugin, OScanTanTanPlugin)
#endif // QT_VERSION < 0x050000
