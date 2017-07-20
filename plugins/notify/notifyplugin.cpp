#include "notifyplugin.h"

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

    m_proxyInter->itemAdded(this, "notify");

    connect(m_popupWidget, &NotifyPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
}

int NotifyPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *NotifyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_notify;
}

QWidget *NotifyPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

const QString NotifyPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-notify";
}

void NotifyPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void NotifyPlugin::popupHide()
{
    m_popupWidget->hideAni();
}
