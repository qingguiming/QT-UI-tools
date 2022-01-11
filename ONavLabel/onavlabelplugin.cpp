#include "onavlabel.h"
#include "onavlabelplugin.h"

#include <QtPlugin>

ONavLabelPlugin::ONavLabelPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ONavLabelPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ONavLabelPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ONavLabelPlugin::createWidget(QWidget *parent)
{
    return new ONavLabel(parent);
}

QString ONavLabelPlugin::name() const
{
    return QLatin1String("ONavLabel");
}

QString ONavLabelPlugin::group() const
{
    return QLatin1String("");
}

QIcon ONavLabelPlugin::icon() const
{
    return QIcon();
}

QString ONavLabelPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ONavLabelPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ONavLabelPlugin::isContainer() const
{
    return false;
}

QString ONavLabelPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ONavLabel\" name=\"oNavLabel\">\n</widget>\n");
}

QString ONavLabelPlugin::includeFile() const
{
    return QLatin1String("onavlabel.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(onavlabelplugin, ONavLabelPlugin)
#endif // QT_VERSION < 0x050000
