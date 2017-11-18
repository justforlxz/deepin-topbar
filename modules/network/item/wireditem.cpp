#include "wireditem.h"
#include "../widgets/fontlabel.h"
#include "../frame/utils/global.h"

#include <QMouseEvent>
#include <QHBoxLayout>

using namespace dtb;
using namespace dtb::network;
using namespace dtb::widgets;

WiredItem::WiredItem(const QString &path)
    : DeviceItem(path)
    , m_connected(false)
    , m_networkLbl(new FontLabel)
    , m_delayTimer(new QTimer(this))
{
    m_delayTimer->setSingleShot(true);
    m_delayTimer->setInterval(20);

    connect(m_networkManager, &NetworkManager::globalNetworkStateChanged, m_delayTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(m_networkManager, &NetworkManager::deviceChanged, this, &WiredItem::deviceStateChanged);
    connect(m_networkManager, &NetworkManager::networkStateChanged, m_delayTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(m_networkManager, &NetworkManager::activeConnectionChanged, this, &WiredItem::activeConnectionChanged);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_networkLbl->setIcon(QChar(0xEC27), FONTSIZE);
    m_networkLbl->setObjectName("NetworkLabel");

    m_networkLbl->setStyleSheet("#NetworkLabel {color: black;}");

    layout->addWidget(m_networkLbl, 0, Qt::AlignCenter);

    setLayout(layout);
}

NetworkDevice::NetworkType WiredItem::type() const
{
    return NetworkDevice::Wired;
}

NetworkDevice::NetworkState WiredItem::state() const
{
    return m_connected ? NetworkDevice::Activated : NetworkDevice::Disconnected;
}

void WiredItem::resizeEvent(QResizeEvent *e)
{
    DeviceItem::resizeEvent(e);

    m_delayTimer->start();
}

void WiredItem::activeConnectionChanged()
{
    m_connected = m_networkManager->activeDeviceSet().contains(m_devicePath);

    m_networkLbl->setStyleSheet(QString(m_connected ? "#NetworkLabel {color: black;}" : "#NetworkLabel {color: red;}"));

    m_delayTimer->start();
}

void WiredItem::deviceStateChanged(const NetworkDevice &device)
{
    if (device.path() != m_devicePath)
        return;

    m_delayTimer->start();
}
