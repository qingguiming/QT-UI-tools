#include "ocombobox.h"
#include "ocomboboxplugin.h"

#include <QtPlugin>

OComboboxPlugin::OComboboxPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void OComboboxPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool OComboboxPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *OComboboxPlugin::createWidget(QWidget *parent)
{
    return new OCombobox(parent);
}

QString OComboboxPlugin::name() const
{
    return QLatin1String("OCombobox");
}

QString OComboboxPlugin::group() const
{
    return QLatin1String("");
}

QIcon OComboboxPlugin::icon() const
{
    return QIcon(QLatin1String(":/mouse.png"));
}

QString OComboboxPlugin::toolTip() const
{
    return QLatin1String("");
}

QString OComboboxPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool OComboboxPlugin::isContainer() const
{
    return false;
}

QString OComboboxPlugin::domXml() const
{
    return QLatin1String("<widget class=\"OCombobox\" name=\"oCombobox\">\n</widget>\n");
}

QString OComboboxPlugin::includeFile() const
{
    return QLatin1String("ocombobox.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(ocomboboxplugin, OComboboxPlugin)
#endif // QT_VERSION < 0x050000
