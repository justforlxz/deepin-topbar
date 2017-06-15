#include "mediacontrolwidget.h"
#include <QHBoxLayout>
#include <QDBusInterface>

MediaControlWidget::MediaControlWidget(QWidget *parent) : QWidget(parent)
{
    initMpris();
    setAttribute(Qt::WA_TranslucentBackground);

    m_mediaControl = new MediaControl(this);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    setLayout(mainLayout);
}

void MediaControlWidget::initMpris()
{
    QDBusInterface *dbusInter = new QDBusInterface("org.freedesktop.DBus", "/", "org.freedesktop.DBus", QDBusConnection::sessionBus(), this);
    if (!dbusInter)
        return;

    QDBusReply<QStringList> response = dbusInter->call("ListNames");
    const QStringList &serviceList = response.value();
    QString service = QString();
    for (const QString &serv : serviceList)
    {
        if (!serv.startsWith("org.mpris.MediaPlayer2."))
            continue;
        service = serv;
        break;
    }

    if (service.isEmpty())
        return;

    qDebug() << "got service: " << service;

    m_mediaInter = new DBusMediaPlayer2(service, "/org/mpris/MediaPlayer2", QDBusConnection::sessionBus(), this);

}
