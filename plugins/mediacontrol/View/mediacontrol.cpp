#include "mediacontrol.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QPixmap>
#include <QDebug>

MediaControl::MediaControl(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    m_lastBtn = new DImageButton(":/img/Icons/next_normal.png",
                                 ":/img/Icons/next_hover.png",
                                 ":/img/Icons/next_press.png");

    m_previousBtn = new DImageButton(":/img/Icons/previous_normal.png",
                                     ":/img/Icons/previous_hover.png",
                                     ":/img/Icons/previous_press.png");
    m_pauseBtn = new DImageButton;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_previousBtn, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(m_pauseBtn, 0, Qt::AlignCenter | Qt::AlignVCenter);
    layout->addWidget(m_lastBtn, 0, Qt::AlignRight | Qt::AlignVCenter);

    setLayout(layout);

    connect(m_previousBtn, &DImageButton::clicked, this, &MediaControl::requestPrevious);
    connect(m_pauseBtn, &DImageButton::clicked, this, &MediaControl::requestPause);
    connect(m_lastBtn, &DImageButton::clicked, this, &MediaControl::requestLast);
}

void MediaControl::setPlayState(MediaControl::PlayState state)
{
    m_playState = state;

    switch (state) {
    case Play: {
        m_pauseBtn->setNormalPic(":/img/Icons/pause_normal.png");
        m_pauseBtn->setHoverPic(":/img/Icons/pause_hover.png");
        m_pauseBtn->setPressPic(":/img/Icons/pause_press.png");
        break;
    }
    case Stop:
        break;
    case Pause: {
        m_pauseBtn->setNormalPic(":/img/Icons/start_normal.png");
        m_pauseBtn->setHoverPic(":/img/Icons/start_hover.png");
        m_pauseBtn->setPressPic(":/img/Icons/start_press.png");
        break;
    }
    case Last:
        break;
    case Previous:
        break;
    default:
        break;
    }
}
