#include "networkplugin.h"
#include "networklistmodel.h"

#include <DHiDPIHelper>

using namespace dtb;
using namespace dtb::network;
using namespace dde;
using namespace dde::network;

DWIDGET_USE_NAMESPACE

NetworkPlugin::NetworkPlugin()
{
    m_networkWidget = new QLabel("网络");
    m_controlPanel = new NetworkControlPanel;
    m_delayRefreshTimer = new QTimer(this);
    m_networkModel = new NetworkModel;
    m_networkWorker = new NetworkWorker(m_networkModel);
    m_listModel = new NetworkListModel;
    m_controlPanel->setModel(m_listModel);
}

const QString NetworkPlugin::pluginName() const
{
    return "Network";
}

void NetworkPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_delayRefreshTimer->setSingleShot(true);
    m_delayRefreshTimer->setInterval(2000);

    connect(m_delayRefreshTimer, &QTimer::timeout, this, &NetworkPlugin::refreshWiredItemVisible);
    connect(m_networkModel, &NetworkModel::deviceListChanged, this, &NetworkPlugin::onDeviceListChanged);

    m_networkWorker->active();
    m_proxyInter->addItem(this, "network");

    onDeviceListChanged(m_networkModel->devices());
}

QWidget *NetworkPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_networkWidget;
}

QWidget *NetworkPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    m_networkWorker->requestWirelessScan();

    return m_controlPanel;
}

void NetworkPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{
    Q_UNUSED(color);
}

void NetworkPlugin::refreshWiredItemVisible()
{

}

void NetworkPlugin::onDeviceListChanged(const QList<NetworkDevice *> devices)
{
    QList<QString> mPaths = m_itemsMap.keys();
    QList<QString> newPaths;

    for (auto device : devices) {
        const QString &path = device->path();
        newPaths << path;
        // new device
        if (!mPaths.contains(path)) {
            mPaths << path;
            m_itemsMap.insert(path, device);
            connect(device, &NetworkDevice::enableChanged, m_delayRefreshTimer, static_cast<void (QTimer:: *)()>(&QTimer::start));
        }
    }

    for (auto mPath : mPaths) {
        // removed device
        if (!newPaths.contains(mPath)) {
            m_itemsMap.take(mPath)->deleteLater();
            break;
        }
    }

//    int wirelessItemCount = wirelessItems.size();
//    for (int i = 0; i < wirelessItemCount; ++i) {
//        QTimer::singleShot(1, [=] {
//            wirelessItems.at(i)->setDeviceInfo(wirelessItemCount == 1 ? -1 : i + 1);
//        });
//    }

    m_listModel->setDeviceList(m_itemsMap);

    if (!m_itemsMap.isEmpty()) {

    }

    m_delayRefreshTimer->start();
}
