#ifndef AccountPLUGIN_H
#define AccountPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include <QObject>

namespace dtb {
namespace account {

class AccountPopupWidget;
class AccountWidget;

class AccountPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    explicit AccountPlugin(QObject *parent = 0);

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    int itemSortKey(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QWidget *itemPopupApplet(const QString &itemKey) Q_DECL_OVERRIDE;

    const QString itemCommand(const QString &itemKey) Q_DECL_OVERRIDE;

    void popupShow() Q_DECL_OVERRIDE;
    void popupHide() Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    AccountPopupWidget *m_popupWidget;
    AccountWidget *m_Account;
};
}
}

#endif // AccountPLUGIN_H
