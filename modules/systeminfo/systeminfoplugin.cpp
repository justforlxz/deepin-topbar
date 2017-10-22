#include "systeminfoplugin.h"

using namespace dtb;
using namespace dtb::systeminfo;

SystemInfoPlugin::SystemInfoPlugin()
{
    m_systeminfo = new SystemInfoWidget;
//    m_popupWidget = new SystemInfoPopupWidget;
}

const QString SystemInfoPlugin::pluginName() const
{
    return "systeminfo";
}

void SystemInfoPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

//    connect(m_popupWidget, &SystemInfoPopupWidget::requestHidePopup, this, [=] {
//        m_proxyInter->requestHidePopup();
//    });

    m_proxyInter->addItem(this, "");
}

QWidget *SystemInfoPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_systeminfo;
}
