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
    return QString("power");
}

void PowerPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *PowerPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QMenu *PowerPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget->menu();
}
