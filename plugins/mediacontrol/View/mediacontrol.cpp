#include "mediacontrol.h"
#include <QHBoxLayout>

MediaControl::MediaControl(QWidget *parent) : QFrame(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedWidth(100);

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

    layout->addWidget(m_previousBtn, 0, Qt::AlignLeft);
    layout->addWidget(m_pauseBtn, 0, Qt::AlignCenter);
    layout->addWidget(m_lastBtn, 0, Qt::AlignRight);

    setLayout(layout);

    connect(m_lastBtn, &DImageButton::clicked, this, &MediaControl::requestLast);
    connect(m_previousBtn, &DImageButton::clicked, this, &MediaControl::requestPrevious);
    connect(m_pauseBtn, &DImageButton::clicked, this, &MediaControl::requestPause);
}
