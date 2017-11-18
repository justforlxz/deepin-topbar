#include "wirelessitem.h"

using namespace dtb;
using namespace dtb::network;
using namespace dtb::widgets;

WirelessItem::WirelessItem(const QString &path)
    : DeviceItem(path)
    , m_wirelessLbl(new FontLabel)
    , m_isConnected(false)
{
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
    connect(m_networkManager, &NetworkManager::activeConnectionChanged, this, &WirelessItem::onActivateConnectChanged);
}

WirelessItem::~WirelessItem()
{
}

NetworkDevice::NetworkType WirelessItem::type() const
{
    return NetworkDevice::Wireless;
}

NetworkDevice::NetworkState WirelessItem::state() const
{
    return m_isConnected ? NetworkDevice::Activated : NetworkDevice::Disconnected;
}

void WirelessItem::init()
{
    m_device = *(m_networkManager->device(m_devicePath));

    m_wirelessLbl->setStyleSheet("#NetworkLabel {color: black;}");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setMargin(0);
    vLayout->setSpacing(0);

    vLayout->addWidget(m_wirelessLbl, 0, Qt::AlignCenter);

    setLayout(vLayout);
}

void WirelessItem::onActivateConnectChanged()
{
    m_isConnected = m_networkManager->activeDeviceSet().contains(m_devicePath);

    m_wirelessLbl->setStyleSheet(QString(m_isConnected ? "#NetworkLabel {color: black;}" : "#NetworkLabel {color: red;}"));
}
