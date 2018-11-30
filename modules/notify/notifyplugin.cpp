#include "notifyplugin.h"
#include "notifypopupwidget.h"
#include "notifywidget.h"

#include <com_deepin_dde_notification.h>

using NotifyInter = com::deepin::dde::Notification;

using namespace dtb;
using namespace dtb::notify;

NotifyPlugin::NotifyPlugin()
{
    m_notify = new NotifyWidget;
    m_popupWidget = new NotifyPopupWidget;
    NotifyInter * notifyInter = new NotifyInter("com.deepin.dde.Notification", "/com/deepin/dde/Notifications", QDBusConnection::sessionBus(), this);


}

const QString NotifyPlugin::pluginName() const
{
    return "Notify";
}

void NotifyPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *NotifyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_notify;
}

QWidget *NotifyPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

void NotifyPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}
