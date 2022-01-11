#include "ocustompie.h"
#include "ocustompieplugin.h"

#include <QtPlugin>

OCustomPiePlugin::OCustomPiePlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OCustomPiePlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OCustomPiePlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OCustomPiePlugin::createWidget(QWidget *parent)
{
    return new OCustomPie(parent);
}

QString OCustomPiePlugin::name() const
{
    return QLatin1String("OCustomPie");
}

QString OCustomPiePlugin::group() const
{
    return QLatin1String("");
}

QIcon OCustomPiePlugin::icon() const
{
    return QIcon();
}

QString OCustomPiePlugin::toolTip() const
{
    return QLatin1String("");
}

QString OCustomPiePlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OCustomPiePlugin::isContainer() const
{
    return false;
}

QString OCustomPiePlugin::domXml() const
{
    return QLatin1String("<widget class=\"OCustomPie\" name=\"oCustomPie\">\n</widget>\n");
}

QString OCustomPiePlugin::includeFile() const
{
    return QLatin1String("ocustompie.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ocustompieplugin, OCustomPiePlugin)
#endif // QT_VERSION < 0x050000
