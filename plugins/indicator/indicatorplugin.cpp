#include "indicatorplugin.h"


IndicatorPlugin::IndicatorPlugin(QObject *parent) : QObject(parent)
{
    m_centralWidget = new Plugin::Indicator::IndicatorWidget;
}

const QString IndicatorPlugin::pluginName() const
{
    return QString("indicator");
}

void IndicatorPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, QString());
}

int IndicatorPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *IndicatorPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *IndicatorPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return nullptr;
}

const QString IndicatorPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("deepin-indicator");
}
