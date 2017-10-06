#include "powerplugin.h"
#include "powerpopupwidget.h"

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

    connect(m_centralWidget, &PowerWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });

    m_proxyInter->addItem(this, "");
}

int PowerPlugin::itemSortKey(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *PowerPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *PowerPlugin::itemPopupApplet(const QString &itemKey) {
    Q_UNUSED(itemKey);
    return nullptr;
}

const QString PowerPlugin::itemCommand(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return QString("deepin-power");
}

void PowerPlugin::popupShow()
{
//    Plugins::Power::PowerPopupWidget *w = qobject_cast<Plugins::Power::PowerPopupWidget *>(m_centralWidget->popup());
//    w->showAni();
}

void PowerPlugin::popupHide()
{
//    Plugins::Power::PowerPopupWidget *w = qobject_cast<Plugins::Power::PowerPopupWidget *>(m_centralWidget->popup());
    //    w->hideAni();
}

QMenu *PowerPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return new QMenu();
}

void PowerPlugin::invokedMenuItem(QAction *action)
{

}
