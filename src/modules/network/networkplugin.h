#ifndef NETWORKPLUGIN_H
#define NETWORKPLUGIN_H

#include "interfaces/pluginsiteminterface.h"

#include "networklistview.h"
#include "networkcontrolpanel.h"

#include <QLabel>
#include <NetworkWorker>
#include <NetworkModel>
#include <NetworkDevice>
#include <QObject>

namespace dtb {
namespace network {
class NetworkListModel;
class NetworkPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    NetworkPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private slots:
    void refreshWiredItemVisible();
    void onDeviceListChanged(const QList<dde::network::NetworkDevice *> devices);

private:
    PluginProxyInterface *m_proxyInter;
    QTimer *m_delayRefreshTimer;
    dde::network::NetworkModel *m_networkModel;
    dde::network::NetworkWorker *m_networkWorker;
    QMap<QString, dde::network::NetworkDevice *> m_itemsMap;
    QLabel *m_networkWidget;
    NetworkListModel *m_listModel;
    NetworkControlPanel *m_controlPanel;
};
}
}

#endif // NETWORKPLUGIN_H
