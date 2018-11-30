#include "accountplugin.h"
#include "accountwidget.h"

namespace dtb {
namespace account {
AccountPlugin::AccountPlugin(QObject *parent)
    : QObject(parent)
{
    m_Account = new AccountWidget;
}

const QString AccountPlugin::pluginName() const
{
    return "account";
}

void AccountPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *AccountPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Account;
}

QMenu *AccountPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Account->menu();
}

}
}
