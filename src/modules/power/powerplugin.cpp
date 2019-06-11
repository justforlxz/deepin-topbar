#include "powerplugin.h"
#include "powerpopupwidget.h"
#include "powermodel.h"

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

    m_systemPowerInter =
            new SystemPowerInter("com.deepin.system.Power", "/com/deepin/system/Power",
                                 QDBusConnection::systemBus(), this);
    m_systemPowerInter->setSync(false);

    m_model = new PowerModel;

    connect(m_systemPowerInter, &SystemPowerInter::BatteryStatusChanged, this, &PowerPlugin::onbatteryStatusChanged);
    connect(m_systemPowerInter, &SystemPowerInter::BatteryPercentageChanged, m_model, &PowerModel::setbatteryPercentage);

    m_popupWidget = new PowerPopupWidget;
    m_popupWidget->setModel(m_model);

    m_proxyInter->addItem(this, "");

    connect(m_centralWidget, &PowerWidget::requestHidePopupWindow, this, [=] {
        m_proxyInter->hidePopupWindow();
    });

    onbatteryStatusChanged(m_systemPowerInter->batteryStatus());
}

QWidget *PowerPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *PowerPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

void PowerPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}

void PowerPlugin::onbatteryStatusChanged(uint state)
{
    m_model->setBatteryStateInfo(static_cast<BatteryState>(state));
}
