#include "mediacontrol.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QPixmap>
#include <QDebug>

MediaControl::MediaControl(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet("QLabel {"
                  "background: transparent;"
                  "}");

    setFixedWidth(100);

    m_lastBtn = new QLabel;
    m_lastBtn->setPixmap(QPixmap(":/img/Icons/next_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
    m_lastBtn->installEventFilter(this);

    m_previousBtn = new QLabel;
    m_previousBtn->setPixmap(QPixmap(":/img/Icons/previous_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
    m_previousBtn->installEventFilter(this);

    m_pauseBtn = new QLabel;
    m_pauseBtn->setPixmap(QPixmap(":/img/Icons/pause_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
    m_pauseBtn->installEventFilter(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_previousBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(m_pauseBtn, 0, Qt::AlignCenter | Qt::AlignVCenter);
    layout->addWidget(m_lastBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

    setLayout(layout);
}

void MediaControl::setPlayState(MediaControl::PlayState state)
{
    m_playState = state;

    switch (state) {
    case Play:
        m_pauseBtn->setPixmap(QPixmap(":/img/Icons/pause_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
        break;
    case Stop:
        break;
    case Pause:
        m_pauseBtn->setPixmap(QPixmap(":/img/Icons/start_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
        break;
    case Last:
        break;
    case Previous:
        break;
    default:
        break;
    }
}

bool MediaControl::eventFilter(QObject *watched, QEvent *event)
{
    if (m_playState == Stop) {
        return false;
    }

    if (watched == m_lastBtn) {
        if (event->type() == QEvent::Enter || event->type() == QEvent::MouseButtonRelease) {
            m_lastBtn->setPixmap(QPixmap(":/img/Icons/next_hover.png").scaled(23, 23, Qt::KeepAspectRatio));
        }
        if (event->type() == QEvent::Leave) {
            m_lastBtn->setPixmap(QPixmap(":/img/Icons/next_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
        }
        if (event->type() == QEvent::MouseButtonPress) {
            m_lastBtn->setPixmap(QPixmap(":/img/Icons/next_press.png").scaled(23, 23, Qt::KeepAspectRatio));
            emit requestLast();
        }
    }

    if (watched == m_previousBtn) {
        if (event->type() == QEvent::Enter || event->type() == QEvent::MouseButtonRelease) {
            m_previousBtn->setPixmap(QPixmap(":/img/Icons/previous_hover.png").scaled(23, 23, Qt::KeepAspectRatio));
        }
        if (event->type() == QEvent::Leave) {
            m_previousBtn->setPixmap(QPixmap(":/img/Icons/previous_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
        }
        if (event->type() == QEvent::MouseButtonPress) {
            m_previousBtn->setPixmap(QPixmap(":/img/Icons/previous_press.png").scaled(23, 23, Qt::KeepAspectRatio));
            emit requestPrevious();
        }
    }

    if (watched == m_pauseBtn) {
        if (m_playState == Pause) {
            if (event->type() == QEvent::Enter || event->type() == QEvent::MouseButtonRelease) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/start_hover.png").scaled(23, 23, Qt::KeepAspectRatio));
            }
            if (event->type() == QEvent::Leave) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/start_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
            }
            if (event->type() == QEvent::MouseButtonPress) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/start_press.png").scaled(23, 23, Qt::KeepAspectRatio));
                emit requestPause();
            }
        }
        if (m_playState == Play) {
            if (event->type() == QEvent::Enter || event->type() == QEvent::MouseButtonRelease) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/pause_hover.png").scaled(23, 23, Qt::KeepAspectRatio));
            }
            if (event->type() == QEvent::Leave) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/pause_normal.png").scaled(23, 23, Qt::KeepAspectRatio));
            }
            if (event->type() == QEvent::MouseButtonPress) {
                m_pauseBtn->setPixmap(QPixmap(":/img/Icons/pause_press.png").scaled(23, 23, Qt::KeepAspectRatio));
                emit requestPause();
            }
        }
    }

    return false;
}
