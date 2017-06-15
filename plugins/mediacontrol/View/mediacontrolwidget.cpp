#include "mediacontrolwidget.h"
#include <QHBoxLayout>
#include <QDBusInterface>

MediaControlWidget::MediaControlWidget(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedWidth(100);

    initMpris();

    m_mediaTitle = new QLabel;
    m_mediaControl = new MediaControl(this);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_mediaTitle);

    setLayout(mainLayout);

    m_mediaControl->move(0, -m_mediaControl->height());

    //Animation
    m_hoverControlAni = new QPropertyAnimation(m_mediaControl, "pos", this);
    m_hoverControlAni->setDuration(300);
    m_hoverControlAni->setStartValue(QPoint(m_mediaControl->x(), 0));
    m_hoverControlAni->setEndValue(QPoint(m_mediaControl->x(), -m_mediaControl->height()));
    m_hoverControlAni->setEasingCurve(QEasingCurve::InOutCubic);

    m_showControlAni = new QPropertyAnimation(m_mediaControl, "pos", this);
    m_showControlAni->setDuration(300);
    m_showControlAni->setStartValue(QPoint(m_mediaControl->x(), -m_mediaControl->height()));
    m_showControlAni->setEndValue(QPoint(m_mediaControl->x(), 0));
    m_showControlAni->setEasingCurve(QEasingCurve::InOutCubic);
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

void MediaControlWidget::enterEvent(QEvent *event)
{
    QFrame::enterEvent(event);

    m_showControlAni->start();
}

void MediaControlWidget::leaveEvent(QEvent *event)
{
     QFrame::leaveEvent(event);

     m_hoverControlAni->start();
}
