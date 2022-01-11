#include "oanimationbutton.h"
#include "oanimationbuttonplugin.h"

#include <QtPlugin>

OAnimationButtonPlugin::OAnimationButtonPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OAnimationButtonPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OAnimationButtonPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OAnimationButtonPlugin::createWidget(QWidget *parent)
{
    return new OAnimationButton(parent);
}

QString OAnimationButtonPlugin::name() const
{
    return QLatin1String("OAnimationButton");
}

QString OAnimationButtonPlugin::group() const
{
    return QLatin1String("");
}

QIcon OAnimationButtonPlugin::icon() const
{
    return QIcon();
}

QString OAnimationButtonPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OAnimationButtonPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OAnimationButtonPlugin::isContainer() const
{
    return false;
}

QString OAnimationButtonPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OAnimationButton\" name=\"oAnimationButton\">\n</widget>\n");
}

QString OAnimationButtonPlugin::includeFile() const
{
    return QLatin1String("oanimationbutton.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oanimationbuttonplugin, OAnimationButtonPlugin)
#endif // QT_VERSION < 0x050000
