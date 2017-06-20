#include "mediacontrol.h"
#include <QHBoxLayout>
#include <QEvent>
#include <QPixmap>
#include <QDebug>

namespace Plugin {
namespace MediaControl {

MediaControl::MediaControl(QWidget *parent) : QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    m_lastBtn = new DImageButton(":/img/Icons/play_next_normal.png",
                                 ":/img/Icons/play_next_hover.png",
                                 ":/img/Icons/play_next_press.png");

    m_previousBtn = new DImageButton(":/img/Icons/play_previous_normal.png",
                                     ":/img/Icons/play_previous_hover.png",
                                     ":/img/Icons/play_previous_press.png");
    m_pauseBtn = new DImageButton;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(2);
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
        m_pauseBtn->setNormalPic(":/img/Icons/play_pause_normal.png");
        m_pauseBtn->setHoverPic(":/img/Icons/play_pause_hover.png");
        m_pauseBtn->setPressPic(":/img/Icons/play_pause_press.png");
        break;
    }
    case Stop:
        break;
    case Pause: {
        m_pauseBtn->setNormalPic(":/img/Icons/play_start_normal.png");
        m_pauseBtn->setHoverPic(":/img/Icons/play_start_hover.png");
        m_pauseBtn->setPressPic(":/img/Icons/play_start_press.png");
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

}
}
