#include "powerplugin.h"
#include "powerwidgetaction.h"

using namespace dtb;
using namespace dtb::power;

PowerPlugin::PowerPlugin(QObject *parent) : QObject(parent) {
    m_centralWidget = new PowerWidget;
}

PowerPlugin::~PowerPlugin() {
    m_centralWidget->deleteLater();
}

const QString PowerPlugin::pluginName() const {
    return QString("Power");
}

void PowerPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");

    connect(m_centralWidget, &PowerWidget::requestHidePopupWindow, this, [=] {
        m_proxyInter->hidePopupWindow();
    });
}

QWidget *PowerPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *PowerPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget->menu();
}

void PowerPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}
