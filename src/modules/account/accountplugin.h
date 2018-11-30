#ifndef AccountPLUGIN_H
#define AccountPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include <QObject>

namespace dtb {
namespace account {

class AccountWidget;

class AccountPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    explicit AccountPlugin(QObject *parent = 0);

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;
    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QMenu* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    AccountWidget *m_Account;
};
}
}

#endif // AccountPLUGIN_H
