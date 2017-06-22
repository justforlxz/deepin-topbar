#ifndef INDICATORPLUGIN_H
#define INDICATORPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "View/indicatorwidget.h"
#include <QLabel>
#include <QObject>

class  IndicatorPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "indicator.json")

public:
    IndicatorPlugin(QObject *parent = 0);

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;

private:
    PluginProxyInterface *m_proxyInter;
    Plugin::Indicator::IndicatorWidget *m_centralWidget;
};

#endif // INDICATORPLUGIN_H
