#include "notifyplugin.h"
#include "notifypopupwidget.h"
#include "notifywidget.h"

using namespace dtb;
using namespace dtb::notify;

NotifyPlugin::NotifyPlugin()
{
    m_notify = new NotifyWidget;
    m_popupWidget = new NotifyPopupWidget;
}

const QString NotifyPlugin::pluginName() const
{
    return "notify";
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

QMenu *NotifyPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return nullptr;
}
