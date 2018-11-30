#include "accountwidget.h"
#include "widgets/fontlabel.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

using namespace dtb;
using namespace dtb::account;

AccountWidget::AccountWidget(QWidget *parent)
    : ContentModule(parent)
{
    m_dbusLogined = new DBusLogined("com.deepin.daemon.Accounts",
                                    "/com/deepin/daemon/Logined",
                                    QDBusConnection::systemBus(), this);
    m_dbusLogined->setSync(true);

    QJsonDocument doc = QJsonDocument::fromJson(m_dbusLogined->userList().toUtf8());
    QJsonArray jsonArray = doc.array();

    for (int i(0); i != jsonArray.count(); ++i) {
        const QJsonObject &obj = jsonArray.at(i).toObject();
        if (obj["Display"].toString().isEmpty())
            continue;

        if (obj["Name"].toString() == getenv("USER")) {
            m_dbusUser = new DBusUser("com.deepin.daemon.Accounts",
                                      "/com/deepin/daemon/Accounts/User" + QString::number(obj["UID"].toInt()),
                                      QDBusConnection::systemBus(), this);

            connect(m_dbusUser, &DBusUser::IconFileChanged, this, &AccountWidget::iconUpdate);
            m_dbusUser->setSync(false);
            m_dbusUser->iconFile();
            break;
        }
    }

    setFixedSize(30, 26);

    m_accountIcon = new QLabel;
    m_accountIcon->setFixedSize(30, 22);

    m_accountIcon->setStyleSheet("QLabel {"
                                 "color: rgb(67, 67, 62);"
                                 "}");

    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(2);
    layout->setSpacing(0);
    layout->addWidget(m_accountIcon, 0, Qt::AlignCenter);

    setLayout(layout);

    initMenu();
}

AccountWidget::~AccountWidget()
{
    m_menu->deleteLater();
}

void AccountWidget::iconUpdate(const QString &file)
{
    if (file.isEmpty())
        return;

    QUrl url(file);
    if (url.isLocalFile())
        return iconUpdate(url.path());

    m_accountIcon->setPixmap(QPixmap(file).scaled(26, 26));
}

void AccountWidget::handleShutdownAction(const QString &action)
{
    const QString command = QString("dbus-send --print-reply --dest=com.deepin.dde.shutdownFront " \
                                    "/com/deepin/dde/shutdownFront " \
                                    "com.deepin.dde.shutdownFront.%1").arg(action);

    QProcess::startDetached(command);
}

void AccountWidget::handleLockAction()
{
    const QString command = QString("dbus-send --print-reply --dest=com.deepin.dde.lockFront " \
                                    "/com/deepin/dde/lockFront " \
                                    "com.deepin.dde.lockFront.Show");

    QProcess::startDetached(command);
}

void AccountWidget::initMenu()
{
    m_menu = new QMenu;

    QAction* m_lock = new QAction(tr("Lock"), this);
    QAction* m_logout = new QAction(tr("Logout"), this);
    QAction* m_suspend = new QAction(tr("Suspend"), this);
    QAction* m_shutdown = new QAction(tr("Shutdown"), this);
    QAction* m_reboot = new QAction(tr("Restart"), this);

    m_menu->addAction(m_lock);
    m_menu->addAction(m_logout);
    m_menu->addAction(m_suspend);
    m_menu->addAction(m_shutdown);
    m_menu->addAction(m_reboot);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(m_lock, &QAction::triggered, this, &AccountWidget::handleLockAction);
    connect(m_logout, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(m_suspend, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(m_shutdown, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(m_reboot, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    signalMapper->setMapping(m_logout, "Logout");
    signalMapper->setMapping(m_suspend, "Suspend");
    signalMapper->setMapping(m_shutdown, "Shutdown");
    signalMapper->setMapping(m_reboot, "Restart");
    connect(signalMapper, static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &AccountWidget::handleShutdownAction);
}
