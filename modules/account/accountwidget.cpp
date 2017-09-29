#include "accountwidget.h"
#include "fontlabel.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

using namespace dtb;
using namespace dtb::account;

AccountWidget::AccountWidget(QWidget *parent) : QLabel(parent)
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

    setStyleSheet("QLabel {"
                  "background: transparent;"
                  "}"
                  "QLabel:hover {"
                  "background: #1E90FF;"
                  "}");

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

    installEventFilter(this);
}

bool AccountWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QMouseEvent::Enter) {
        m_accountIcon->setStyleSheet("background: transparent;"
                                    "color: white;");
    }

    if (event->type() == QMouseEvent::Leave) {
        m_accountIcon->setStyleSheet("background: transparent;"
                                    "color: rgb(67, 67, 62);");
    }

    return false;
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
