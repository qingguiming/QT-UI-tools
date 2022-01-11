#include "orulertemp.h"
#include "orulertempplugin.h"

#include <QtPlugin>

ORulerTempPlugin::ORulerTempPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void ORulerTempPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool ORulerTempPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *ORulerTempPlugin::createWidget(QWidget *parent)
{
    return new ORulerTemp(parent);
}

QString ORulerTempPlugin::name() const
{
    return QLatin1String("ORulerTemp");
}

QString ORulerTempPlugin::group() const
{
    return QLatin1String("");
}

QIcon ORulerTempPlugin::icon() const
{
    return QIcon();
}

QString ORulerTempPlugin::toolTip() const
{
    return QLatin1String("");
}

QString ORulerTempPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool ORulerTempPlugin::isContainer() const
{
    return false;
}

QString ORulerTempPlugin::domXml() const
{
    return QLatin1String("<widget class=\"ORulerTemp\" name=\"oRulerTemp\">\n</widget>\n");
}

QString ORulerTempPlugin::includeFile() const
{
    return QLatin1String("orulertemp.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(orulertempplugin, ORulerTempPlugin)
#endif // QT_VERSION < 0x050000
