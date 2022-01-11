#include "oimageanimation.h"
#include "oimageanimationplugin.h"

#include <QtPlugin>

OImageAnimationPlugin::OImageAnimationPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OImageAnimationPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OImageAnimationPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OImageAnimationPlugin::createWidget(QWidget *parent)
{
    return new OImageAnimation(parent);
}

QString OImageAnimationPlugin::name() const
{
    return QLatin1String("OImageAnimation");
}

QString OImageAnimationPlugin::group() const
{
    return QLatin1String("");
}

QIcon OImageAnimationPlugin::icon() const
{
    return QIcon();
}

QString OImageAnimationPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OImageAnimationPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OImageAnimationPlugin::isContainer() const
{
    return false;
}

QString OImageAnimationPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OImageAnimation\" name=\"oImageAnimation\">\n</widget>\n");
}

QString OImageAnimationPlugin::includeFile() const
{
    return QLatin1String("oimageanimation.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(oimageanimationplugin, OImageAnimationPlugin)
#endif // QT_VERSION < 0x050000
