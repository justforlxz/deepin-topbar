#include "mediacontrolwidget.h"
#include <QHBoxLayout>
#include <QDBusInterface>

MediaControlWidget::MediaControlWidget(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedWidth(100);

    m_mediaTitle = new QLabel(this);
    m_mediaControl = new MediaControl(this);

    m_mediaControl->move(0, -m_mediaControl->height());
    m_mediaTitle->move(0, 0);


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

    connect(m_hoverControlAni, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
        m_mediaTitle->move(0, 30 + value.toPoint().y());
    });

    connect(m_showControlAni, &QPropertyAnimation::valueChanged ,this, [=](const QVariant &value) {
        m_mediaTitle->move(0, 30 + value.toPoint().y());
    });

    initMpris();
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

    connect(m_mediaInter, &DBusMediaPlayer2::MetadataChanged, this, [=]{
        const QString text = m_mediaInter->metadata().value("xesam:title").toString();
        QFontMetrics qfm(m_mediaTitle->font());

        if (qfm.width(text) > m_mediaTitle->width())
            m_mediaTitle->setText(qfm.elidedText(text, Qt::ElideRight, m_mediaTitle->width()));
        else
            m_mediaTitle->setText(text);
    });

    connect(m_mediaInter, &DBusMediaPlayer2::PlaybackStatusChanged, this, [=]{
        if (m_mediaInter->playbackStatus() == "Playing")
            m_mediaControl->setPlayState(MediaControl::Play);
        if (m_mediaInter->playbackStatus() == "Stopped")
            m_mediaControl->setPlayState(MediaControl::Stop);
        if (m_mediaInter->playbackStatus() == "Paused")
            m_mediaControl->setPlayState(MediaControl::Pause);
    });

    connect(m_mediaControl, &MediaControl::requestLast, m_mediaInter, &DBusMediaPlayer2::Next);
    connect(m_mediaControl, &MediaControl::requestPrevious, m_mediaInter, &DBusMediaPlayer2::Previous);
    connect(m_mediaControl, &MediaControl::requestPause, m_mediaInter, &DBusMediaPlayer2::PlayPause);

    m_mediaInter->MetadataChanged();
    m_mediaInter->PlaybackStatusChanged();
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
