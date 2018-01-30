#include "wirelessitem.h"
#include "applet/accesspoint.h"
#include "../frame/utils/global.h"
#include "applet/refreshaction.h"

using namespace dtb;
using namespace dtb::network;
using namespace dtb::widgets;

WirelessItem::WirelessItem(const QString &path)
    : DeviceItem(path)
    , m_wirelessLbl(new FontLabel)
    , m_isConnected(false)
    , m_activeAP(AccessPoint())
{
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
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

    m_networkInter = new DBusNetwork(this);

    m_updateAPTimer = new QTimer(this);

    m_updateAPTimer->setSingleShot(true);
    m_updateAPTimer->setInterval(100);

    m_pwdDialog = new Dtk::Widget::DInputDialog(nullptr);

    m_wirelessLbl->setStyleSheet("#NetworkLabel {color: black;}");
    m_wirelessLbl->setIcon(QChar(0xE908), FONTSIZE);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setMargin(0);
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(10, 0, 10,0);

    vLayout->addWidget(m_wirelessLbl, 0, Qt::AlignCenter);

    setLayout(vLayout);

    connect(m_networkManager, &NetworkManager::activeConnectionChanged, this, &WirelessItem::onActivateConnectChanged);
    connect(m_networkInter, &DBusNetwork::AccessPointAdded, this, &WirelessItem::APAdded);
    connect(m_networkInter, &DBusNetwork::AccessPointRemoved, this, &WirelessItem::APRemoved);
    connect(m_networkInter, &DBusNetwork::AccessPointPropertiesChanged, this, &WirelessItem::APPropertiesChanged);
    connect(m_networkInter, &DBusNetwork::DevicesChanged, this, &WirelessItem::deviceStateChanged);
    connect(m_networkInter, &DBusNetwork::NeedSecrets, this, &WirelessItem::needSecrets);
    connect(m_networkInter, &DBusNetwork::DeviceEnabled, this, &WirelessItem::deviceEnabled);

    connect(m_networkInter, &DBusNetwork::NeedSecretsFinished, m_pwdDialog, &Dtk::Widget::DInputDialog::close);
    connect(m_pwdDialog, &Dtk::Widget::DInputDialog::textValueChanged, [this] {m_pwdDialog->setTextAlert(false);});
    connect(m_pwdDialog, &Dtk::Widget::DInputDialog::cancelButtonClicked, this, &WirelessItem::pwdDialogCanceled);
    connect(m_pwdDialog, &Dtk::Widget::DInputDialog::accepted, this, &WirelessItem::pwdDialogAccepted);

    connect(m_updateAPTimer, &QTimer::timeout, this, &WirelessItem::updateAPList);

    connect(this, &WirelessItem::activeAPChanged, m_updateAPTimer, static_cast<void (QTimer::*)()>(&QTimer::start));

    RefreshAction *refreshAction = new RefreshAction;

    m_refreshTimer = new QTimer(this);
    m_refreshTimer->setInterval(10 * 1000);

    connect(m_refreshTimer, &QTimer::timeout, this, [=] {
        m_networkInter->RequestWirelessScan();
        refreshAction->setIsRefresh(true);

        QTimer::singleShot(7 * 1000, this, [=] {
            refreshAction->setIsRefresh(false);
        });
    });

    m_separator = new QAction(this);
    m_joinOther = new QAction(tr("Join Other Network..."), this);
    m_preferences = new QAction(tr("Open Network Preferences..."), this);

    connect(m_menu, &QMenu::aboutToShow, m_refreshTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
    connect(m_menu, &QMenu::aboutToHide, m_refreshTimer, &QTimer::stop);

    connect(m_menu, &QMenu::triggered, this, [=] (QAction *action) {
        if (action == m_joinOther)
            QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowPage \"string:network\" \"string:network\"");
        if (action == m_preferences)
            QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:network\"");
    });

    DActionLabel *action = new DActionLabel(refreshAction);

    m_menu->addAction(action);

    m_separator->setSeparator(true);

    m_menu->addAction(m_separator);
    m_menu->addAction(m_joinOther);
    m_menu->addAction(m_preferences);

    loadAPList();
    onActiveAPChanged();
}

void WirelessItem::onActivateConnectChanged()
{
    m_isConnected = m_networkManager->activeDeviceSet().contains(m_devicePath);

    m_wirelessLbl->setStyleSheet(QString(m_isConnected ? "#NetworkLabel {color: black;}" : "#NetworkLabel {color: red;}"));
}

void WirelessItem::deviceEnabled(const QString &devPath, const bool enable)
{
    if (devPath != m_device.path())
        return;

    if (!enable)
        m_wirelessLbl->setIcon(QChar(0xE791), FONTSIZE);
}

void WirelessItem::deviceStateChanged()
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

                if (prevInfo.activeAp() != m_device.activeAp())
                    onActiveAPChanged();

                break;
            }
        }
        break;
    }
}

void WirelessItem::APAdded(const QString &devPath, const QString &info)
{
    if (devPath != m_device.path())
        return;

    AccessPoint ap(info);
    if (m_apList.contains(ap))
        return;

    m_apList.append(ap);

    m_updateAPTimer->start();
}

void WirelessItem::APRemoved(const QString &devPath, const QString &info)
{
    if (devPath != m_device.path())
        return;

    AccessPoint ap(info);
    if (ap.ssid() == m_activeAP.ssid())
        return;

    // NOTE: if one ap removed, prehaps another ap has same ssid, so we need to refersh ap list instead of remove it
    m_apList.clear();
    loadAPList();
}

void WirelessItem::APPropertiesChanged(const QString &devPath, const QString &info)
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
}

void WirelessItem::loadAPList()
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

void WirelessItem::onActiveAPChanged()
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

void WirelessItem::updateAPList()
{
    const bool isEnabled = m_networkManager->deviceEnabled(m_devicePath);
    setVisible(isEnabled);

    if (isEnabled) {
        // sort ap list by strength
        std::sort(m_apList.begin(), m_apList.end(), std::greater<AccessPoint>());

        do {
            if (m_apList.size() > m_apwLists.size()) {
                const int i = m_apList.size() - m_apwLists.size();
                for (int index = 0; index != i; index++) {
                    AccessPointWidget *apw = new AccessPointWidget;
                    DActionLabel *action = new DActionLabel(apw);

                    m_apwLists << apw;
                    m_acList << action;
                    m_menu->addAction(action);

                    connect(apw, &AccessPointWidget::requestActiveAP, this, &WirelessItem::activateAP, Qt::UniqueConnection);
                    connect(apw, &AccessPointWidget::requestDeactiveAP, this, &WirelessItem::deactiveAP, Qt::UniqueConnection);
                }
            } else if (m_apList.size() < m_apwLists.size() && !m_apwLists.isEmpty()) {
                int i = m_apwLists.size() - m_apList.size();
                for (int index = 0; index != i; index++) {
                    DActionLabel *action = m_acList.last();
                    AccessPointWidget *apw = m_apwLists.last();

                    m_menu->removeAction(action);

                    m_apwLists.removeLast();
                    m_acList.removeLast();

                    action->deleteLater();
                    apw->deleteLater();
                }
            }
        } while(m_apList.size() != m_apwLists.size());

        for (int i = 0; i != m_apList.size(); i++) {
            AccessPointWidget *apw = m_apwLists[i];
            const AccessPoint &ap = m_apList[i];
            apw->updateAP(ap);
            apw->setActiveState(NetworkDevice::Disconnected);
        }

        if (m_activeAP.strength()) {
            AccessPointWidget *apw = m_apwLists[m_apList.indexOf(m_activeAP)];
            apw->setActiveState(m_device.state());

            const int i = m_activeAP.strength();

            if (i <= 20)
                m_wirelessLbl->setIcon(QChar(0xE904), FONTSIZE);
            else if (i <= 40)
                m_wirelessLbl->setIcon(QChar(0xE905), FONTSIZE);
            else if (i <= 60)
                m_wirelessLbl->setIcon(QChar(0xE906), FONTSIZE);
            else if (i <= 80)
                m_wirelessLbl->setIcon(QChar(0xE907), FONTSIZE);
            else
                m_wirelessLbl->setIcon(QChar(0xE908), FONTSIZE);

        }

        m_menu->addAction(m_separator);
        m_menu->addAction(m_joinOther);
        m_menu->addAction(m_preferences);
    }
}

void WirelessItem::needSecrets(const QString &info)
{
    const QJsonObject infoObject = QJsonDocument::fromJson(info.toUtf8()).object();

    const QString connPath = infoObject.value("ConnectionPath").toString();
    const QString security = infoObject.value("SettingName").toString();
    const QString ssid = infoObject.value("ConnectionId").toString();

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

    m_pwdDialog->setTitle(tr("Password required to connect to <font color=\"#faca57\">%1</font>").arg(ssid));

    // clear old config
    m_pwdDialog->setTextEchoMode(QLineEdit::Password);
    m_pwdDialog->setTextValue(QString());

    if (!m_pwdDialog->isVisible())
        m_pwdDialog->show();
}

void WirelessItem::pwdDialogAccepted()
{
    if (m_pwdDialog->textValue().isEmpty())
        return m_pwdDialog->setTextAlert(true);
    m_networkInter->FeedSecret(m_lastConnPath, m_lastConnSecurity, m_pwdDialog->textValue(), true);
}

void WirelessItem::pwdDialogCanceled()
{
    m_networkInter->CancelSecret(m_lastConnPath, m_lastConnSecurity);
    m_pwdDialog->close();
}

void WirelessItem::activateAP(const QDBusObjectPath &apPath, const QString &ssid)
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

void WirelessItem::deactiveAP()
{
    m_activeAP = AccessPoint();
    m_networkInter->DisconnectDevice(QDBusObjectPath(m_device.path()));
}
