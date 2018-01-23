#include "networkplugin.h"

using namespace dtb;
using namespace dtb::network;

NetworkPlugin::NetworkPlugin()
{
    m_network = new NetworkWidget;
    m_refershTimer = new QTimer(this);
    m_networkManager = NetworkManager::instance(this);
}

const QString NetworkPlugin::pluginName() const
{
    return "Network";
}

void NetworkPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_refershTimer->setInterval(100);
    m_refershTimer->setSingleShot(true);

    connect(m_networkManager, &NetworkManager::deviceAdded, this, &NetworkPlugin::deviceAdded);
    connect(m_networkManager, &NetworkManager::deviceRemoved, this, &NetworkPlugin::deviceRemoved);

    m_networkManager->init();

    m_proxyInter->addItem(this, "network");
}

QWidget *NetworkPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_network;
}

void NetworkPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

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

    m_deviceItemList.append(item);

    m_network->addItem(item);
}

void NetworkPlugin::deviceRemoved(const NetworkDevice &device)
{
    const auto item = std::find_if(m_deviceItemList.begin(), m_deviceItemList.end(),
                                   [&] (DeviceItem *dev) {return device == dev->path();});

    if (item == m_deviceItemList.cend())
        return;

    m_network->remove(*item);

    (*item)->deleteLater();
    m_deviceItemList.erase(item);
}
