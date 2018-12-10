#include "sounditem.h"
#include "soundapplet.h"
#include "dbus/dbussink.h"
#include "componments/volumeslider.h"
#include "widgets/dwidgetaction.h"
#include "sinkinputwidget.h"
#include "componments/mediacontrol.h"
#include "frame/utils/global.h"

#include <QPainter>
#include <QIcon>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <DHiDPIHelper>

DWIDGET_USE_NAMESPACE

// menu actions
#define MUTE    "mute"
#define SETTINS "settings"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundItem::SoundItem(QWidget *parent)
    : ContentModule(parent)
    , m_tickScrollArea(new QScrollArea(this))
    , m_mprisTitle(new QLabel)
    , m_tickEffect(new DTickEffect(m_mprisTitle, m_mprisTitle))
    , m_fontLabel(new QLabel)
    , m_mprisInter(nullptr)
    , m_mediaControl(new MediaControl)
    , m_applet(new SoundApplet(this))
    , m_sinkInter(nullptr)
    , m_menu(new QMenu(this))
{
    setStyleSheet("QLabel {color: #d3d3d3;}");

    m_tickScrollArea->setWidget(m_mprisTitle);
    m_tickScrollArea->setObjectName("scrollarea");
    m_tickScrollArea->setWidgetResizable(true);
    m_tickScrollArea->setFocusPolicy(Qt::NoFocus);
    m_tickScrollArea->setFrameStyle(QFrame::NoFrame);
    m_tickScrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_tickScrollArea->setContentsMargins(0, 0, 0, 0);
    m_tickScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tickScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_tickScrollArea->setStyleSheet("background-color:transparent;");
    m_tickScrollArea->hide();

    m_tickEffect->setDirection(DTickEffect::RightToLeft);
    m_tickEffect->setDuration(3000);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(3);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_tickScrollArea, 0, Qt::AlignCenter);
    layout->addWidget(m_mediaControl, 0, Qt::AlignCenter);
    layout->addWidget(m_fontLabel, 0, Qt::AlignCenter);

    setLayout(layout);

    m_mprisTitle->setVisible(false);
    m_mediaControl->setVisible(false);

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

bool SoundItem::isSoundItem(const QPoint &cursor) const {
    return m_fontLabel->geometry().contains(mapFromGlobal(cursor));
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

    QPixmap pixmap;

    if (mute) {
        pixmap = DHiDPIHelper::loadNxPixmap(":/image/image/mute.svg");
    }
    else {
        if (volume / 1000.0f >= 0.7f)
            pixmap = DHiDPIHelper::loadNxPixmap(":/image/image/full.svg");
        else if (volume / 1000.0f >= 0.4f)
            pixmap = DHiDPIHelper::loadNxPixmap(":/image/image/half.svg");
        else if (volume / 1000.0f >= 0.2f)
            pixmap = DHiDPIHelper::loadNxPixmap(":/image/image/low.svg");
        else
            pixmap = DHiDPIHelper::loadNxPixmap(":/image/image/empty.svg");
    }

    m_fontLabel->setPixmap(pixmap);
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

    emit requestHidePopupWindow();
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

   m_mediaControl->setVisible(true);

   connect(m_mediaControl, &MediaControl::requestLast, m_mprisInter, &DBusMediaPlayer2::Next, Qt::UniqueConnection);
   connect(m_mediaControl, &MediaControl::requestPrevious, m_mprisInter, &DBusMediaPlayer2::Previous, Qt::UniqueConnection);
   connect(m_mediaControl, &MediaControl::requestPause, m_mprisInter, &DBusMediaPlayer2::PlayPause, Qt::UniqueConnection);

    connect(m_mprisInter, &DBusMediaPlayer2::MetadataChanged, this, [=]{
        const auto &   meta        = m_mprisInter->metadata();
        const QString &title       = meta.value("xesam:title").toString();
        const QString &artist      = meta.value("xesam:artist").toString();

        if (title.isEmpty()) {
            m_mprisTitle->clear();
            m_tickEffect->stop();
        }
        else {
            if (artist.isEmpty()) {
                m_mprisTitle->setText(title);
            }
            else {
                m_mprisTitle->setText(QString(" %1 - %2 ").arg(title).arg(artist));
            }
        }

        const int width { fontMetrics().width(title) };
        m_tickScrollArea->setFixedWidth(std::min(std::max(width, 100), 200));

        m_mprisTitle->adjustSize();
        m_tickEffect->play();
    });

    connect(m_mprisInter, &DBusMediaPlayer2::PlaybackStatusChanged, this, [=]{
       if (m_mprisInter->playbackStatus() == "Playing") {
           m_mediaControl->setPlayState(MediaControl::Play);
       }
       if (m_mprisInter->playbackStatus() == "Stopped") {
           m_mediaControl->setPlayState(MediaControl::Stop);
       }
       if (m_mprisInter->playbackStatus() == "Paused")
           m_mediaControl->setPlayState(MediaControl::Pause);

        m_mprisInter->MetadataChanged();
    });

    m_mprisInter->MetadataChanged();
    m_mprisInter->PlaybackStatusChanged();

    m_mprisTitle->setVisible(true);
    m_tickScrollArea->show();
    m_tickEffect->play();
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

   m_mediaControl->setVisible(false);

    m_mprisTitle->setVisible(false);
    m_tickScrollArea->hide();
    m_tickEffect->stop();
}
