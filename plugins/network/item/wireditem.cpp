#include "constants.h"
#include "wireditem.h"
#include <QPainter>
#include <QMouseEvent>
#include <QIcon>

WiredItem::WiredItem(const QString &path)
    : DeviceItem(path),

      m_connected(false),
      m_itemTips(new QLabel(this)),
      m_delayTimer(new QTimer(this))
{
//    QIcon::setThemeName("deepin");

    m_delayTimer->setSingleShot(true);
    m_delayTimer->setInterval(20);

    m_itemTips->setObjectName("wired-" + path);
    m_itemTips->setVisible(false);
    m_itemTips->setStyleSheet("color:white;"
                              "padding:0px 3px;");

    connect(m_delayTimer, &QTimer::timeout, this, &WiredItem::reloadIcon);

    connect(m_networkManager, &NetworkManager::globalNetworkStateChanged, m_delayTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(m_networkManager, &NetworkManager::deviceChanged, this, &WiredItem::deviceStateChanged);
    connect(m_networkManager, &NetworkManager::networkStateChanged, m_delayTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(m_networkManager, &NetworkManager::activeConnectionChanged, this, &WiredItem::activeConnectionChanged);
}

NetworkDevice::NetworkType WiredItem::type() const
{
    return NetworkDevice::Wired;
}

NetworkDevice::NetworkState WiredItem::state() const
{
    return m_connected ? NetworkDevice::Activated : NetworkDevice::Disconnected;
}

QWidget *WiredItem::itemPopup()
{
    m_itemTips->setText(tr("Unknow"));

    do {
        if (!m_connected)
        {
            m_itemTips->setText(tr("No Network"));
            break;
        }

        const QJsonObject info = m_networkManager->deviceConnInfo(m_devicePath);
        if (!info.contains("Ip4"))
            break;
        const QJsonObject ipv4 = info.value("Ip4").toObject();
        if (!ipv4.contains("Address"))
            break;
        m_itemTips->setText(tr("Wired connection: %1").arg(ipv4.value("Address").toString()));
    } while (false);

    return m_itemTips;
}

const QString WiredItem::itemCommand() const
{
    return "dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:network\"";
}

void WiredItem::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.drawPixmap(rect().center() - m_icon.rect().center(), m_icon);
}

void WiredItem::resizeEvent(QResizeEvent *e)
{
    DeviceItem::resizeEvent(e);

    m_delayTimer->start();
}

void WiredItem::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::RightButton)
        return QWidget::mousePressEvent(e);

    const QPoint p(e->pos() - rect().center());
    if (p.manhattanLength() < std::min(width(), height()) * 0.8 * 0.5)
    {
        emit requestContextMenu();
        return;
    }

    return QWidget::mousePressEvent(e);
}

void WiredItem::refreshIcon()
{
    m_delayTimer->start();
}

void WiredItem::reloadIcon()
{
    Q_ASSERT(sender() == m_delayTimer);

    const Dock::DisplayMode displayMode = qApp->property(PROP_DISPLAY_MODE).value<Dock::DisplayMode>();

    QString iconName = "network-";
    if (!m_connected)
    {
        NetworkDevice::NetworkState devState = m_networkManager->deviceState(m_devicePath);

        if (devState < NetworkDevice::Disconnected)
            iconName.append("error");
        else
            iconName.append("offline");
    } else {
        NetworkManager::GlobalNetworkState gState = m_networkManager->globalNetworkState();

        if (gState == NetworkManager::ConnectedGlobal)
            iconName.append("online");
        else
            iconName.append("idle");
    }

    if (displayMode == Dock::Efficient)
        iconName.append("-symbolic");

    const int size = displayMode == Dock::Efficient ? 16 : std::min(width(), height()) * 0.8;
    m_icon = QIcon::fromTheme(iconName).pixmap(size, size);
    update();
}

void WiredItem::activeConnectionChanged()
{
//    if (path != m_devicePath)
//        return;

    m_connected = m_networkManager->activeDeviceSet().contains(m_devicePath);
    m_delayTimer->start();
}

void WiredItem::deviceStateChanged(const NetworkDevice &device)
{
    if (device.path() != m_devicePath)
        return;
    m_delayTimer->start();
}
