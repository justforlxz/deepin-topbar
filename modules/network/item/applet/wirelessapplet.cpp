#include "wirelessapplet.h"
#include "accesspointwidget.h"

#include <QJsonDocument>
#include <QScreen>
#include <QScreen>
#include <QGuiApplication>

#include <dinputdialog.h>

DWIDGET_USE_NAMESPACE

#define WIDTH           300
#define MAX_HEIGHT      300
#define ITEM_HEIGHT     30

WirelessList::WirelessList(const QSet<NetworkDevice>::const_iterator &deviceIter, QWidget *parent)
    : QScrollArea(parent),

      m_device(*deviceIter),
      m_activeAP(),

      m_updateAPTimer(new QTimer(this)),
      m_pwdDialog(new DInputDialog(nullptr)),
      m_autoConnBox(new QCheckBox),

      m_centralLayout(new QVBoxLayout),
      m_centralWidget(new QWidget),
      m_controlPanel(new DeviceControlWidget),
      m_networkInter(new DBusNetwork(this))
{
    setFixedHeight(WIDTH);

    m_autoConnBox->setText(tr("Auto-connect"));

    m_pwdDialog->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
    m_pwdDialog->setTextEchoMode(DLineEdit::Password);
    m_pwdDialog->setIcon(QIcon::fromTheme("notification-network-wireless-full"));
    m_pwdDialog->addSpacing(10);
    m_pwdDialog->addContent(m_autoConnBox, Qt::AlignLeft);
    m_pwdDialog->setOkButtonText(tr("Connect"));
    m_pwdDialog->setCancelButtonText(tr("Cancel"));

    m_updateAPTimer->setSingleShot(true);
    m_updateAPTimer->setInterval(100);

    m_centralWidget->setFixedWidth(WIDTH);
    m_centralWidget->setLayout(m_centralLayout);

//    m_centralLayout->addWidget(m_controlPanel);
    m_centralLayout->setSpacing(0);
    m_centralLayout->setMargin(0);

    setWidget(m_centralWidget);
    setFrameStyle(QFrame::NoFrame);
    setFixedWidth(300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color:transparent;");

    connect(m_networkInter, &DBusNetwork::AccessPointAdded, this, &WirelessList::APAdded);
    connect(m_networkInter, &DBusNetwork::AccessPointRemoved, this, &WirelessList::APRemoved);
    connect(m_networkInter, &DBusNetwork::AccessPointPropertiesChanged, this, &WirelessList::APPropertiesChanged);
    connect(m_networkInter, &DBusNetwork::DevicesChanged, this, &WirelessList::deviceStateChanged);
    connect(m_networkInter, &DBusNetwork::NeedSecrets, this, &WirelessList::needSecrets);
    connect(m_networkInter, &DBusNetwork::DeviceEnabled, this, &WirelessList::deviceEnabled);

    connect(m_controlPanel, &DeviceControlWidget::deviceEnableChanged, this, &WirelessList::deviceEnableChanged);

    connect(m_updateAPTimer, &QTimer::timeout, this, &WirelessList::updateAPList);

    connect(this, &WirelessList::activeAPChanged, m_updateAPTimer, static_cast<void (QTimer::*)()>(&QTimer::start));

    connect(m_networkInter, &DBusNetwork::NeedSecretsFinished, m_pwdDialog, &DInputDialog::close);
    connect(m_pwdDialog, &DInputDialog::textValueChanged, [this] {m_pwdDialog->setTextAlert(false);});
    connect(m_pwdDialog, &DInputDialog::cancelButtonClicked, this, &WirelessList::pwdDialogCanceled);
    connect(m_pwdDialog, &DInputDialog::accepted, this, &WirelessList::pwdDialogAccepted);

    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

WirelessList::~WirelessList()
{
    m_pwdDialog->deleteLater();
}

NetworkDevice::NetworkState WirelessList::wirelessState() const
{
    return m_device.state();
}

int WirelessList::activeAPStrgength() const
{
    return m_activeAP.strength();
}

QWidget *WirelessList::controlPanel()
{
    return m_controlPanel;
}

void WirelessList::init()
{
    loadAPList();
    onActiveAPChanged();
    deviceStateChanged();
}

void WirelessList::APAdded(const QString &devPath, const QString &info)
{
    if (devPath != m_device.path())
        return;

    AccessPoint ap(info);
    if (m_apList.contains(ap))
        return;

    m_apList.append(ap);
    m_updateAPTimer->start();
}

void WirelessList::APRemoved(const QString &devPath, const QString &info)
{
    if (devPath != m_device.path())
        return;

    AccessPoint ap(info);
    if (ap.ssid() == m_activeAP.ssid())
        return;

//    m_apList.removeOne(ap);
//    m_updateAPTimer->start();

    // NOTE: if one ap removed, prehaps another ap has same ssid, so we need to refersh ap list instead of remove it
    m_apList.clear();
    loadAPList();
}

void WirelessList::setDeviceInfo(const int index)
{
    // set device enable state
    m_controlPanel->setDeviceEnabled(m_networkInter->IsDeviceEnabled(m_device.dbusPath()));

    // set device name
    if (index == -1)
        m_controlPanel->setDeviceName(tr("Wireless Network"));
    else
        m_controlPanel->setDeviceName(tr("Wireless Network %1").arg(index));
}

void WirelessList::loadAPList()
{
    const QString data = m_networkInter->GetAccessPoints(m_device.dbusPath());
    const QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    Q_ASSERT(doc.isArray());

    for (auto item : doc.array())
    {
        Q_ASSERT(item.isObject());

        AccessPoint ap(item.toObject());
        if (!m_apList.contains(ap))
            m_apList.append(ap);
    }

    m_updateAPTimer->start();
}

void WirelessList::APPropertiesChanged(const QString &devPath, const QString &info)
{
    if (devPath != m_device.path())
        return;

    QJsonDocument doc = QJsonDocument::fromJson(info.toUtf8());
    Q_ASSERT(doc.isObject());
    const AccessPoint ap(doc.object());

    auto it = std::find_if(m_apList.begin(), m_apList.end(),
                           [&] (const AccessPoint &a) {return a == ap;});

    if (it == m_apList.end())
        return;

    *it = ap;
    if (m_activeAP.path() == ap.path())
    {
        m_activeAP = ap;
        emit activeAPChanged();
    }

//    if (*it > ap)
//    {
//        *it = ap;
//        m_activeAP = ap;
//        m_updateAPTimer->start();

//        emit activeAPChanged();
//    }
}

void WirelessList::updateAPList()
{
    Q_ASSERT(sender() == m_updateAPTimer);

    // remove old items
    while (QLayoutItem *item = m_centralLayout->takeAt(0))
    {
        delete item->widget();
        delete item;
    }

    int avaliableAPCount = 0;

    if (m_networkInter->IsDeviceEnabled(m_device.dbusPath()))
    {
        // sort ap list by strength
        std::sort(m_apList.begin(), m_apList.end(), std::greater<AccessPoint>());
//        const bool wirelessActived = m_device.state() == NetworkDevice::Activated;

        for (auto ap : m_apList)
        {
            AccessPointWidget *apw = new AccessPointWidget(ap);
            apw->setFixedHeight(ITEM_HEIGHT);
            if (ap == m_activeAP)
                apw->setActiveState(m_device.state());

            connect(apw, &AccessPointWidget::requestActiveAP, this, &WirelessList::activateAP);
            connect(apw, &AccessPointWidget::requestDeactiveAP, this, &WirelessList::deactiveAP);

            if(apw->active()) {
                m_centralLayout->insertWidget(0, apw);
            } else {
                m_centralLayout->addWidget(apw);
            }

            ++avaliableAPCount;
        }
    }
//    m_controlPanel->setSeperatorVisible(avaliableAPCount);

    const int contentHeight = avaliableAPCount * ITEM_HEIGHT;
    m_centralWidget->setFixedHeight(contentHeight);
    setFixedHeight(std::min(contentHeight, MAX_HEIGHT));
}

void WirelessList::deviceEnableChanged(const bool enable)
{
    m_networkInter->EnableDevice(m_device.dbusPath(), enable);
    m_updateAPTimer->start();
}

void WirelessList::deviceStateChanged()
{
    const QJsonDocument doc = QJsonDocument::fromJson(m_networkInter->devices().toUtf8());
    Q_ASSERT(doc.isObject());
    const QJsonObject obj = doc.object();

    for (auto infoList(obj.constBegin()); infoList != obj.constEnd(); ++infoList)
    {
        Q_ASSERT(infoList.value().isArray());

        if (infoList.key() != "wireless")
            continue;

        const auto list = infoList.value().toArray();
        for (auto i(0); i != list.size(); ++i)
        {
            const QJsonObject info = list[i].toObject();
            if (info.value("Path") == m_device.path())
            {
                const NetworkDevice prevInfo = m_device;
                m_device = NetworkDevice(NetworkDevice::Wireless, info);

                setDeviceInfo(list.size() == 1 ? -1 : i + 1);

                if (prevInfo.state() != m_device.state())
                    emit wirelessStateChanged(m_device.state());
                if (prevInfo.activeAp() != m_device.activeAp())
                    onActiveAPChanged();

                break;
            }
        }
        break;
    }

}

void WirelessList::onActiveAPChanged()
{
    const QJsonDocument doc = QJsonDocument::fromJson(m_networkInter->GetAccessPoints(m_device.dbusPath()).value().toUtf8());
    Q_ASSERT(doc.isArray());

    for (auto dev : doc.array())
    {
        Q_ASSERT(dev.isObject());
        const QJsonObject obj = dev.toObject();

        if (obj.value("Path").toString() != m_device.activeAp())
            continue;

        m_activeAP = AccessPoint(obj);
        break;
    }

    emit activeAPChanged();
}

void WirelessList::pwdDialogAccepted()
{
    if (m_pwdDialog->textValue().isEmpty())
        return m_pwdDialog->setTextAlert(true);
    m_networkInter->FeedSecret(m_lastConnPath, m_lastConnSecurity, m_pwdDialog->textValue(), m_autoConnBox->isChecked());
}

void WirelessList::pwdDialogCanceled()
{
    m_networkInter->CancelSecret(m_lastConnPath, m_lastConnSecurity);
    m_pwdDialog->close();
}

void WirelessList::deviceEnabled(const QString &devPath, const bool enable)
{
    if (devPath != m_device.path())
        return;

    m_controlPanel->setDeviceEnabled(enable);
}

void WirelessList::activateAP(const QDBusObjectPath &apPath, const QString &ssid)
{
    QString uuid;

    const QJsonDocument doc = QJsonDocument::fromJson(m_networkInter->connections().toUtf8());
    for (auto it : doc.object().value("wireless").toArray())
    {
        const QJsonObject obj = it.toObject();
        if (obj.value("Ssid").toString() != ssid)
            continue;
        if (obj.value("HwAddress").toString() != m_device.hwAddress())
            continue;

        uuid = obj.value("Uuid").toString();
        if (!uuid.isEmpty())
            break;
    }

    m_networkInter->ActivateAccessPoint(uuid, apPath, m_device.dbusPath()).waitForFinished();
}

void WirelessList::deactiveAP()
{
    m_activeAP = AccessPoint();
    m_networkInter->DisconnectDevice(QDBusObjectPath(m_device.path()));
}

void WirelessList::needSecrets(const QString &info)
{
    const QJsonObject infoObject = QJsonDocument::fromJson(info.toUtf8()).object();

    const QString connPath = infoObject.value("ConnectionPath").toString();
    const QString security = infoObject.value("SettingName").toString();
    const QString ssid = infoObject.value("ConnectionId").toString();
    const bool defaultAutoConnect = infoObject.value("AutoConnect").toBool();

    // check is our device' ap
    QString connHwAddr;
    QJsonDocument conns = QJsonDocument::fromJson(m_networkInter->connections().toUtf8());
    for (auto item : conns.object()["wireless"].toArray())
    {
        auto info = item.toObject();
        if (info["Path"].toString() != connPath)
            continue;
        connHwAddr = info["HwAddress"].toString();
        break;
    }
    if (connHwAddr != m_device.hwAddress())
        return;

    m_lastConnPath = connPath;
    m_lastConnSecurity = security;

    m_autoConnBox->setChecked(defaultAutoConnect);
    m_pwdDialog->setTitle(tr("Password required to connect to <font color=\"#faca57\">%1</font>").arg(ssid));

    // clear old config
    m_pwdDialog->setTextEchoMode(QLineEdit::Password);
    m_pwdDialog->setTextValue(QString());

    // check if controlcenter handle this request
//    QDBusInterface iface("com.deepin.dde.ControlCenter",
//                         "/com/deepin/dde/ControlCenter/Network",
//                         "com.deepin.dde.ControlCenter.Network");
//    if (iface.isValid() && iface.call("active").arguments().first().toBool())
//        return m_pwdDialog->hide();

    if (!m_pwdDialog->isVisible())
        m_pwdDialog->show();
}
