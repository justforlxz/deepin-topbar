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
    : ContentModule(parent)
    , m_fontLabel(new FontLabel)
    , m_applet(new SoundApplet(this))
    , m_sinkInter(nullptr)
    , m_menu(new QMenu)
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


    // new actions

    QAction *advanced = new QAction(tr("Advanced Settings"), this);

    m_menu->addAction(m_applet);

    m_menu->addSeparator();

    m_menu->addAction(advanced);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(advanced, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    signalMapper->setMapping(advanced, 1);
    connect(signalMapper, static_cast<void (QSignalMapper::*)(const int)>(&QSignalMapper::mapped), this, &SoundItem::handleAction);
}

QMenu* SoundItem::menu() const
{
    return m_menu;
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

void SoundItem::handleAction(const int &action)
{
    switch (action) {
    case 1:
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:sound\"");
        break;
    default:
        break;
    }
}
