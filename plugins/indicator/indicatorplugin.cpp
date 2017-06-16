#include "indicatorplugin.h"


IndicatorPlugin::IndicatorPlugin(QObject *parent) : QObject(parent)
{
    m_centralWidget = new IndicatorWidget;
    m_tip = new QLabel;
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

QWidget *IndicatorPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_tip;
}

const QString IndicatorPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("dde-indicator");
}

const QString IndicatorPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString();
}

void IndicatorPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)
    Q_UNUSED(menuId)
}
