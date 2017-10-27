#include "sounditem.h"
#include "soundapplet.h"
#include "dbussink.h"
#include "fontlabel.h"
#include "componments/volumeslider.h"

#include <QPainter>
#include <QIcon>
#include <QMouseEvent>
#include <QVBoxLayout>

// menu actions
#define MUTE    "mute"
#define SETTINS "settings"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundItem::SoundItem(QWidget *parent)
    : QWidget(parent),
      m_fontLabel(new FontLabel),
      m_applet(new SoundApplet(this)),
      m_sinkInter(nullptr)
{
    setObjectName("SoundItem");
    m_applet->setVisible(false);

    setFixedSize(26, 26);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_fontLabel, 0, Qt::AlignHCenter);

    setLayout(layout);

    connect(m_applet, static_cast<void (SoundApplet::*)(DBusSink*) const>(&SoundApplet::defaultSinkChanged), this, &SoundItem::sinkChanged);

    refershIcon();
}

QWidget *SoundItem::popupApplet()
{
    return m_applet;
}

void SoundItem::wheelEvent(QWheelEvent *e)
{
    QWheelEvent *event = new QWheelEvent(e->pos(), e->delta(), e->buttons(), e->modifiers());
    qApp->postEvent(m_applet->mainSlider(), event);

    refershIcon();
    e->accept();
}

void SoundItem::refershIcon()
{
    if (!m_sinkInter)
        return;

    const double volume = m_applet->volumeValue();
    const bool mute = m_sinkInter->mute();

    if (mute) {
        m_fontLabel->setIcon(QChar(0xE198), 14);
        return;
    }

    if (volume >= 1000)
        m_fontLabel->setIcon(QChar(0xE995), 14);
    else if (volume / 1000.0f >= 0.4f)
        m_fontLabel->setIcon(QChar(0xE994), 14);
    else if (volume / 1000.0f >= 0.2f)
        m_fontLabel->setIcon(QChar(0xE993), 14);
    else
        m_fontLabel->setIcon(QChar(0xE992), 14);
}

void SoundItem::sinkChanged(DBusSink *sink)
{
    m_sinkInter = sink;

    connect(m_sinkInter, &DBusSink::MuteChanged, this, &SoundItem::refershIcon);
    connect(m_sinkInter, &DBusSink::VolumeChanged, this, &SoundItem::refershIcon);
    refershIcon();
}
