#ifndef POWERPLUGIN_H
#define POWERPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "powerwidget.h"
#include <QObject>

class PowerPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "power.json")

public:
    PowerPlugin(QObject *parent = 0);
    ~PowerPlugin();

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;

    void popupShow() override;
    void popupHide() override;

    QMenu* itemContextMenu(const QString &itemKey);
    void invokedMenuItem(QAction *action);

private:
    PluginProxyInterface *m_proxyInter;
    Plugins::Power::PowerWidget *m_centralWidget;
};

#endif // POWERPLUGIN_H
