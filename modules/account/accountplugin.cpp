#include "accountplugin.h"
#include "accountpopupwidget.h"
#include "accountwidget.h"

namespace dtb {
namespace account {
AccountPlugin::AccountPlugin(QObject *parent)
    : QObject(parent)
{
    m_Account = new AccountWidget;
    m_popupWidget = new AccountPopupWidget;
}

const QString AccountPlugin::pluginName() const
{
    return "account";
}

void AccountPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    connect(m_popupWidget, &AccountPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
}

int AccountPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *AccountPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Account;
}

QWidget *AccountPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QWidget * w = qobject_cast<QWidget*>(m_popupWidget);

    return w;
}

const QString AccountPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-account";
}

void AccountPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void AccountPlugin::popupHide()
{
    m_popupWidget->hideAni();
}
}
}
