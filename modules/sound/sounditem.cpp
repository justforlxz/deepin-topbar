#include "sounditem.h"
#include "soundapplet.h"
#include "dbussink.h"
#include "fontlabel.h"
#include "componments/volumeslider.h"
#include "dwidgetaction.h"
#include "sinkinputwidget.h"
#include "componments/mediacontrol.h"
#include "utils/global.h"

#include <QPainter>
#include <QIcon>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>

// menu actions
#define MUTE    "mute"
#define SETTINS "settings"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundItem::SoundItem(QWidget *parent)
    : ContentModule(parent)
    , m_mprisTitle(new QLabel)
    , m_fontLabel(new FontLabel)
    , m_mprisInter(nullptr)
//    , m_mediaControl(new MediaControl)
    , m_applet(new SoundApplet(this))
    , m_sinkInter(nullptr)
    , m_menu(new QMenu)
{
    setStyleSheet("QLabel {color: #d3d3d3;}");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(3);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_mprisTitle, 0, Qt::AlignCenter);
//    layout->addWidget(m_mediaControl, 0, Qt::AlignCenter);
    layout->addWidget(m_fontLabel, 0, Qt::AlignCenter);

    setLayout(layout);

    m_mprisTitle->setVisible(false);
//    m_mediaControl->setVisible(false);

    connect(m_applet, static_cast<void (SoundApplet::*)(DBusSink*) const>(&SoundApplet::defaultSinkChanged), this, &SoundItem::sinkChanged);

    refershIcon();

    m_appletAction = new DWidgetAction(m_applet);

    // new actions

    QAction *advanced = new QAction(tr("Advanced Settings"), this);

    m_separator = new QAction(this);
    m_separator->setSeparator(true);

    m_menu->addAction(m_appletAction);

    m_menu->addSeparator();

    m_menu->addAction(m_separator);

    m_menu->addAction(advanced);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(advanced, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    signalMapper->setMapping(advanced, 1);
    connect(signalMapper, static_cast<void (QSignalMapper::*)(const int)>(&QSignalMapper::mapped), this, &SoundItem::handleAction);

    connect(m_applet, &SoundApplet::addNew, this, &SoundItem::addNewInput);
    connect(m_applet, &SoundApplet::removeAll, this, &SoundItem::clearAllInput);

    initMpris();
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

void SoundItem::clearAllInput()
{
    QMapIterator<DWidgetAction*, SinkInputWidget*> i(m_inputMap);

    while (i.hasNext()) {
        i.next();

        m_menu->removeAction(i.key());
        i.key()->deleteLater();
        i.value()->deleteLater();
    }

    m_inputMap.clear();
}

void SoundItem::addNewInput(SinkInputWidget *w)
{
    DWidgetAction *action = new DWidgetAction(w);
    m_menu->insertAction(m_separator, action);
    m_inputMap[action] = w;
}

void SoundItem::initMpris() {
    m_dbusInter = new DBusInterface("org.freedesktop.DBus", "/org/freedesktop/DBus", QDBusConnection::sessionBus(), this);

    connect(m_dbusInter, &DBusInterface::NameOwnerChanged, this, &SoundItem::onNameOwnerChanged);

    for (const auto &name : m_dbusInter->ListNames().value())
        onNameOwnerChanged(name, QString(), name);
}

void SoundItem::onNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOwner) {
    Q_UNUSED(oldOwner);

    if (!name.startsWith("org.mpris.MediaPlayer2."))
        return;

    qDebug() << name << oldOwner << newOwner;

    if (newOwner.isEmpty())
        removeMPRISPath(name);
    else
        loadMPRISPath(name);
}

void SoundItem::loadMPRISPath(const QString &path) {
    m_lastPath = path;

    // save paths
    if (!m_mprisPaths.contains(path))
        m_mprisPaths.append(path);

    if (m_mprisInter)
        m_mprisInter->deleteLater();

    m_mprisInter = new DBusMPRIS(path, "/org/mpris/MediaPlayer2", QDBusConnection::sessionBus(), this);

//    m_mediaControl->setVisible(true);

//    connect(m_mediaControl, &MediaControl::requestLast, m_mprisInter, &DBusMediaPlayer2::Next, Qt::UniqueConnection);
//    connect(m_mediaControl, &MediaControl::requestPrevious, m_mprisInter, &DBusMediaPlayer2::Previous, Qt::UniqueConnection);
//    connect(m_mediaControl, &MediaControl::requestPause, m_mprisInter, &DBusMediaPlayer2::PlayPause, Qt::UniqueConnection);

    connect(m_mprisInter, &DBusMediaPlayer2::MetadataChanged, this, [=]{
        m_mprisTitle->setText(m_mprisInter->metadata().value("xesam:title").toString() + " ");
    });

    connect(m_mprisInter, &DBusMediaPlayer2::PlaybackStatusChanged, this, [=]{
//        if (m_mprisInter->playbackStatus() == "Playing") {
//            m_mediaControl->setPlayState(MediaControl::Play);
//        }
//        if (m_mprisInter->playbackStatus() == "Stopped") {
//            m_mediaControl->setPlayState(MediaControl::Stop);
//        }
//        if (m_mprisInter->playbackStatus() == "Paused")
//            m_mediaControl->setPlayState(MediaControl::Pause);

        m_mprisInter->MetadataChanged();
    });

    m_mprisInter->MetadataChanged();
    m_mprisInter->PlaybackStatusChanged();

    m_mprisTitle->setVisible(true);
}

void SoundItem::removeMPRISPath(const QString &path) {
    m_mprisPaths.removeOne(path);

    if (m_lastPath != path)
        return;

    if (!m_mprisInter)
        return;

    if (!m_mprisPaths.isEmpty())
        return loadMPRISPath(m_mprisPaths.last());

    m_mprisInter->deleteLater();
    m_mprisInter = nullptr;

//    m_mediaControl->setVisible(false);

    m_mprisTitle->setVisible(false);
}
