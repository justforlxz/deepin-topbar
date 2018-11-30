#ifndef AccountWIDGET_H
#define AccountWIDGET_H

#include "frame/item/contentmodule.h"
#include <com_deepin_daemon_logined.h>
#include <com_deepin_daemon_accounts_user.h>
#include <QLabel>
#include <QMenu>

using DBusLogined = com::deepin::daemon::Logined;
using DBusUser = com::deepin::daemon::accounts::User;

namespace dtb {
namespace account {
class AccountWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit AccountWidget(QWidget *parent = 0);
    ~AccountWidget();

    inline QMenu *menu() { return m_menu;}

private slots:
    void iconUpdate(const QString &file);
    void handleShutdownAction(const QString &action);
    void handleLockAction();

private:
    void initMenu();

private:
    QLabel *m_accountIcon;
    DBusLogined *m_dbusLogined;
    DBusUser *m_dbusUser;
    QMenu *m_menu;
};
}
}

#endif // AccountWIDGET_H
