#include "powerplugin.h"
#include "powerpopupwidget.h"

PowerPlugin::PowerPlugin(QObject *parent) : QObject(parent) {
    m_centralWidget = new Plugins::Power::PowerWidget;

}

PowerPlugin::~PowerPlugin() {
    m_centralWidget->deleteLater();
}

const QString PowerPlugin::pluginName() const {
    return QString("power");
}

void PowerPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, QString());

    connect(m_centralWidget, &Plugins::Power::PowerWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
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
    return m_centralWidget->popup();
}

const QString PowerPlugin::itemCommand(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return QString("deepin-power");
}

void PowerPlugin::popupShow()
{
    Plugins::Power::PowerPopupWidget *w = qobject_cast<Plugins::Power::PowerPopupWidget *>(m_centralWidget->popup());
    w->showAni();
}

void PowerPlugin::popupHide()
{
    Plugins::Power::PowerPopupWidget *w = qobject_cast<Plugins::Power::PowerPopupWidget *>(m_centralWidget->popup());
    w->hideAni();
}
