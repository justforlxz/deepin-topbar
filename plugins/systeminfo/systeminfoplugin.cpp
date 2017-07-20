#include "systeminfoplugin.h"

SystemInfoPlugin::SystemInfoPlugin()
{
    m_systeminfo = new SystemInfoWidget;
    m_popupWidget = new SystemInfoPopupWidget;
}

const QString SystemInfoPlugin::pluginName() const
{
    return "systeminfo";
}

void SystemInfoPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, "systeminfo");

    connect(m_popupWidget, &SystemInfoPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
}

int SystemInfoPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *SystemInfoPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_systeminfo;
}

QWidget *SystemInfoPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

const QString SystemInfoPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-systeminfo";
}

void SystemInfoPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void SystemInfoPlugin::popupHide()
{
    m_popupWidget->hideAni();
}
