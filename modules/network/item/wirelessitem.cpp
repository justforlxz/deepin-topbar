
#include "wirelessitem.h"

#include <QPainter>
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPixmap>

using namespace dtb;
using namespace dtb::network;

WirelessItem::WirelessItem(const QString &path)
    : DeviceItem(path),

      m_refershTimer(new QTimer(this)),
      m_wirelessApplet(new QWidget),
      m_wirelessPopup(new QLabel),
      m_APList(nullptr)
{
    m_refershTimer->setSingleShot(false);
    m_refershTimer->setInterval(100);

    m_wirelessApplet->setVisible(false);
    m_wirelessPopup->setObjectName("wireless-" + m_devicePath);
    m_wirelessPopup->setVisible(false);
    m_wirelessPopup->setStyleSheet("color:white;"
                                   "padding: 0px 3px;");

    connect(m_refershTimer, &QTimer::timeout, this, static_cast<void (WirelessItem::*)()>(&WirelessItem::update));
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

WirelessItem::~WirelessItem()
{
    m_APList->deleteLater();
    m_APList->controlPanel()->deleteLater();
}

NetworkDevice::NetworkType WirelessItem::type() const
{
    return NetworkDevice::Wireless;
}

NetworkDevice::NetworkState WirelessItem::state() const
{
    return m_APList->wirelessState();
}

QWidget *WirelessItem::itemApplet()
{
    return m_wirelessApplet;
}

QWidget *WirelessItem::itemPopup()
{
    const NetworkDevice::NetworkState stat = state();

    m_wirelessPopup->setText(tr("No Network"));

    if (stat == NetworkDevice::Activated)
    {
        const QJsonObject obj = m_networkManager->deviceConnInfo(m_devicePath);
        if (obj.contains("Ip4"))
        {
            const QJsonObject ip4 = obj["Ip4"].toObject();
            if (ip4.contains("Address"))
            {
                m_wirelessPopup->setText(tr("Wireless Connection: %1").arg(ip4["Address"].toString()));
            }
        }
    }

    return m_wirelessPopup;
}

bool WirelessItem::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_APList && e->type() == QEvent::Resize)
        QMetaObject::invokeMethod(this, "adjustHeight", Qt::QueuedConnection);

    return false;
}

void WirelessItem::resizeEvent(QResizeEvent *e)
{
    DeviceItem::resizeEvent(e);

    m_icons.clear();
}

const QPixmap WirelessItem::iconPix(const int size)
{
    QString type;

    const auto state = m_APList->wirelessState();
    if (state <= NetworkDevice::Disconnected)
    {
        type = "disconnect";
        m_refershTimer->stop();
    }
    else
    {
        int strength = 0;
        if (state == NetworkDevice::Activated)
        {
            strength = m_APList->activeAPStrgength();
            m_refershTimer->stop();
        }
        else
        {
            strength = QTime::currentTime().msec() / 10 % 100;
            if (!m_refershTimer->isActive())
                m_refershTimer->start();
        }

        if (strength == 100)
            type = "8";
        else
            type = QString::number(strength / 10 & ~0x1);
    }

    const QString key = QString("wireless-%1%2")
                                .arg(type)
                                .arg("-symbolic");

    return cachedPix(key, size);
}

const QPixmap WirelessItem::cachedPix(const QString &key, const int size)
{
    if (!m_icons.contains(key)) {

        QPixmap pixmap(size, size);
        QSvgRenderer renderer(":/wireless/resources/wireless/" + key + ".svg");
        pixmap.fill(Qt::transparent);

        QPainter painter;
        painter.begin(&pixmap);
        renderer.render(&painter);
        painter.end();

        m_icons.insert(key, pixmap);
    }

    return m_icons.value(key);
}

void WirelessItem::init()
{
    const auto devInfo = m_networkManager->device(m_devicePath);

    m_APList = new WirelessList(devInfo);
    m_APList->installEventFilter(this);
    m_APList->setObjectName("wireless-" + m_devicePath);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(m_APList->controlPanel());
    vLayout->addWidget(m_APList);
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    m_wirelessApplet->setLayout(vLayout);

    connect(m_APList, &WirelessList::activeAPChanged, this, static_cast<void (WirelessItem::*)()>(&WirelessItem::update));
    connect(m_APList, &WirelessList::wirelessStateChanged, this, static_cast<void (WirelessItem::*)()>(&WirelessItem::update));
}

void WirelessItem::adjustHeight()
{
    m_wirelessApplet->setFixedHeight(m_APList->height() + m_APList->controlPanel()->height());
}
