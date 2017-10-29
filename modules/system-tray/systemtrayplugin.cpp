#include "systemtrayplugin.h"

#include <QWindow>
#include <QWidget>
#include <QX11Info>

#include <xcb/xcb_icccm.h>

using namespace dtb;
using namespace dtb::systemtray;

SystemTrayPlugin::SystemTrayPlugin(QObject *parent)
    : QObject(parent),
      m_trayInter(new DBusTrayManager(this)),
      m_trayApplet(new TrayApplet),
      m_tipsLabel(new QLabel),

      m_containerSettings(new QSettings("deepin", "dde-dock-tray"))
{
    m_trayApplet->setObjectName("sys-tray");

    m_tipsLabel->setObjectName("sys-tray");
    m_tipsLabel->setText(tr("System Tray"));
    m_tipsLabel->setVisible(false);
    m_tipsLabel->setStyleSheet("color:white;"
                               "padding: 0 3px;");
}

const QString SystemTrayPlugin::pluginName() const
{
    return "system-tray";
}

void SystemTrayPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "system-tray");

    connect(m_trayInter, &DBusTrayManager::TrayIconsChanged, this, &SystemTrayPlugin::trayListChanged);
    connect(m_trayInter, &DBusTrayManager::Changed, this, &SystemTrayPlugin::trayChanged);

    m_trayInter->Manage();

    QTimer::singleShot(1, this, &SystemTrayPlugin::trayListChanged);
}

QWidget *SystemTrayPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_trayApplet;
}

QWidget *SystemTrayPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_tipsLabel;
}

QWidget *SystemTrayPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return nullptr;
}

bool SystemTrayPlugin::itemAllowContainer(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return true;
}

bool SystemTrayPlugin::itemIsInContainer(const QString &itemKey)
{
    const QString widKey = getWindowClass(itemKey.toInt());
    if (widKey.isEmpty())
        return false;

    return m_containerSettings->value(widKey, false).toBool();
}

int SystemTrayPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

void SystemTrayPlugin::setItemIsInContainer(const QString &itemKey, const bool container)
{
    m_containerSettings->setValue(getWindowClass(itemKey.toInt()), container);
}

void SystemTrayPlugin::updateTipsContent()
{
    auto trayList = m_trayList.values();

    m_trayApplet->clear();
    m_trayApplet->addWidgets(trayList);
}

const QString SystemTrayPlugin::getWindowClass(quint32 winId)
{
    auto *connection = QX11Info::connection();

    auto *reply = new xcb_icccm_get_wm_class_reply_t;
    auto *error = new xcb_generic_error_t;
    auto cookie = xcb_icccm_get_wm_class(connection, winId);
    auto result = xcb_icccm_get_wm_class_reply(connection, cookie, reply, &error);

    QString ret;
    if (result == 1)
    {
        ret = QString("%1-%2").arg(reply->class_name).arg(reply->instance_name);
        xcb_icccm_get_wm_class_reply_wipe(reply);
    }

    delete reply;
    delete error;

    return ret;
}

void SystemTrayPlugin::trayListChanged()
{
    // sleep some times wait dock add icons;

    QEventLoop loop;
    QTimer::singleShot(800, &loop, &QEventLoop::quit);
    loop.exec();

    QList<quint32> trayList = m_trayInter->trayIcons();

    for (auto tray : m_trayList.keys())
        if (!trayList.contains(tray))
            trayRemoved(tray);

    for (auto tray : trayList)
        trayAdded(tray);
}

void SystemTrayPlugin::trayAdded(const quint32 winId)
{
    if (m_trayList.contains(winId))
        return;

    getWindowClass(winId);

    TrayWidget *trayWidget = new TrayWidget(winId);

    m_trayList[winId] = trayWidget;

    m_trayApplet->addWidget(trayWidget);
}

void SystemTrayPlugin::trayRemoved(const quint32 winId)
{
    if (!m_trayList.contains(winId))
        return;

    TrayWidget *widget = m_trayList[winId];

    m_trayList.remove(winId);
    widget->deleteLater();

    updateTipsContent();
}

void SystemTrayPlugin::trayChanged(const quint32 winId)
{
    if (!m_trayList.contains(winId))
        return;

    m_trayList[winId]->updateIcon();
}
