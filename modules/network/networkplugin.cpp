#include "networkplugin.h"

using namespace dtb;
using namespace dtb::network;

NetworkPlugin::NetworkPlugin()
{
    m_network = new NetworkWidget;
    m_popupWidget = new NetworkPopupWidget;

    m_networkManager = NetworkManager::instance(this);
}

const QString NetworkPlugin::pluginName() const
{
    return "network";
}

void NetworkPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    connect(m_popupWidget, &NetworkPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });

    connect(m_networkManager, &NetworkManager::deviceAdded, this, &NetworkPlugin::deviceAdded);
    connect(m_networkManager, &NetworkManager::deviceRemoved, this, &NetworkPlugin::deviceRemoved);

    m_networkManager->init();
}

int NetworkPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *NetworkPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // return widget have main layout
    // all network widget in this widget;

    return m_network;
}

QWidget *NetworkPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

//    return m_popupWidget;

    for (auto deviceItem : m_deviceItemList) {
        continue;
        return deviceItem->itemApplet();
    }
//        if (deviceItem->path() == itemKey)
//            return deviceItem->itemCommand();

    return nullptr;

}

const QString NetworkPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-network";
}

void NetworkPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void NetworkPlugin::popupHide()
{
    m_popupWidget->hideAni();
}

void NetworkPlugin::deviceAdded(const NetworkDevice &device)
{
    DeviceItem *item = nullptr;
    switch (device.type())
    {
    case NetworkDevice::Wired:      item = new WiredItem(device.path());        break;
    case NetworkDevice::Wireless:   item = new WirelessItem(device.path());     break;
    default:;
    }

    if (!item)
        return;
//    connect(item, &DeviceItem::requestContextMenu, this, &NetworkPlugin::contextMenuRequested);

    m_deviceItemList.append(item);
}

void NetworkPlugin::deviceRemoved(const NetworkDevice &device)
{
    const auto item = std::find_if(m_deviceItemList.begin(), m_deviceItemList.end(),
                                   [&] (DeviceItem *dev) {return device == dev->path();});

    if (item == m_deviceItemList.cend())
        return;

    (*item)->deleteLater();
    m_deviceItemList.erase(item);
}

void NetworkPlugin::networkStateChanged(const NetworkDevice::NetworkTypes &states)
{

}

void NetworkPlugin::deviceTypesChanged(const NetworkDevice::NetworkTypes &types)
{

}
