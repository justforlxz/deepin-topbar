#ifndef AccountWIDGET_H
#define AccountWIDGET_H

#include <com_deepin_daemon_logined.h>
#include <com_deepin_daemon_accounts_user.h>
#include <QLabel>

using DBusLogined = com::deepin::daemon::Logined;
using DBusUser = com::deepin::daemon::accounts::User;

namespace dtb {
namespace account {
class AccountWidget : public QLabel
{
    Q_OBJECT
public:
    explicit AccountWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void iconUpdate(const QString &file);

private:
    QLabel *m_accountIcon;
    DBusLogined *m_dbusLogined;
    DBusUser *m_dbusUser;
};
}
}

#endif // AccountWIDGET_H
