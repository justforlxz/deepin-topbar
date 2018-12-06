#include "mainframe.h"

#include "frame/utils/global.h"

#include <QScreen>
#include <QApplication>
#include <QRect>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>
#include <DPlatformWindowHandle>
#include <DForeignWindow>
#include <QTimer>
#include <DWindowManagerHelper>

DWIDGET_USE_NAMESPACE

#define DOCK_POS_TOP 0
#define DOCK_POS_RIGHT 1
#define DOCK_POS_BOTTOM 2
#define DOCK_POS_LEFT 3

MainFrame::MainFrame(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    init();
    initAnimation();
    initConnect();

    QTimer::singleShot(0, this, &MainFrame::screenChanged);
    QTimer::singleShot(0, this, &MainFrame::onWindowListChanged);
}

MainFrame::~MainFrame()
{
    m_dockInter->deleteLater();
    m_desktopWidget->deleteLater();
}

/*
     Think zccrs, Perfect protection against launcher. It won't stop launcher at last.
     */

void MainFrame::init()
{
    m_desktopWidget = QApplication::desktop();

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    setAttribute(Qt::WA_TranslucentBackground);
    setMaskColor(DBlurEffectWidget::DarkColor);

    m_mainPanel = new dtb::MainPanel(this);

    m_showWithLauncher =new QPropertyAnimation(m_mainPanel, "pos", m_mainPanel);
    m_showWithLauncher->setDuration(300);
    m_showWithLauncher->setStartValue(QPoint(m_mainPanel->x(), -m_mainPanel->height()));
    m_showWithLauncher->setEndValue(QPoint(m_mainPanel->x(), 0));
    m_showWithLauncher->setEasingCurve(QEasingCurve::InOutCubic);

    m_hideWithLauncher =new QPropertyAnimation(m_mainPanel, "pos", m_mainPanel);
    m_hideWithLauncher->setDuration(300);
    m_hideWithLauncher->setStartValue(QPoint(m_mainPanel->x(), 0));
    m_hideWithLauncher->setEndValue(QPoint(m_mainPanel->x(), -m_mainPanel->height()));
    m_hideWithLauncher->setEasingCurve(QEasingCurve::InOutCubic);

    m_dockInter = new DockInter("com.deepin.dde.daemon.Dock",
                                "/com/deepin/dde/daemon/Dock",
                                QDBusConnection::sessionBus(),
                                this);
}

void MainFrame::initConnect()
{
    connect(m_desktopWidget, &QDesktopWidget::resized, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);
    connect(m_desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);

    connect(m_dockInter, &DockInter::DisplayModeChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);
    connect(m_dockInter, &DockInter::HideModeChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);
    connect(m_dockInter, &DockInter::PositionChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);
    connect(m_dockInter, &DockInter::IconSizeChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);
    connect(m_dockInter, &DockInter::FrontendWindowRectChanged, this, &MainFrame::delayedScreenChanged, Qt::QueuedConnection);

    connect(DWindowManagerHelper::instance(), &DWindowManagerHelper::windowListChanged, this, &MainFrame::onWindowListChanged);
}

void MainFrame::initAnimation()
{
    m_launchAni = new QPropertyAnimation(this, "pos", this);
    m_launchAni->setDuration(1000);
    m_launchAni->setEasingCurve(QEasingCurve::OutBounce);

    connect(m_showWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
        move(value.toPoint());
        update();
    });

    connect(m_hideWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
        move(value.toPoint());
        update();
    });
}

void MainFrame::showSetting()
{
    QTimer::singleShot(1, m_mainPanel, &dtb::MainPanel::showSettingDialog);
}

void MainFrame::delayedScreenChanged()
{
    QTimer::singleShot(1000, this, &MainFrame::screenChanged);
}

void MainFrame::screenChanged()
{
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DOCK;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    xcb_ewmh_wm_strut_partial_t strutPartial;
    memset(&strutPartial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    // clear strut partial
    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winId(), strutPartial);

    // set strct partial
    xcb_ewmh_wm_strut_partial_t strut_partial;
    memset(&strut_partial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    const QRect dockRect = m_dockInter->frontendWindowRect();
    const QRect primaryRect = QApplication::primaryScreen()->geometry();

    switch (m_dockInter->position()) {
    case DOCK_POS_BOTTOM:
        strut_partial.top = TOPHEIGHT * devicePixelRatioF();
        strut_partial.top_start_x = primaryRect.x();
        strut_partial.top_end_x = primaryRect.x() + primaryRect.width();

        setFixedSize(primaryRect.width(), TOPHEIGHT);
        move(primaryRect.x(), primaryRect.y());
        m_mainPanel->resize(primaryRect.width(), TOPHEIGHT);
        m_mainPanel->move(0, 0);
        break;
    case DOCK_POS_LEFT:
        strut_partial.top = TOPHEIGHT * devicePixelRatioF();
        strut_partial.top_start_x = primaryRect.x();
        strut_partial.top_end_x = primaryRect.x() + primaryRect.width();

        if (dockRect.bottomRight().y() + TOPHEIGHT >= primaryRect.height()) {
            m_mainPanel->resize(primaryRect.width() - dockRect.topRight().x(), TOPHEIGHT);
            m_mainPanel->move(0, 0);
            setFixedSize(primaryRect.width() - dockRect.topRight().x(), TOPHEIGHT);
            move(primaryRect.x() + dockRect.topRight().x(), primaryRect.y());
        }
        else {
            m_mainPanel->resize(primaryRect.width(), TOPHEIGHT);
            m_mainPanel->move(0, 0);
            setFixedSize(primaryRect.width(), TOPHEIGHT);
            move(primaryRect.x(), primaryRect.y());
        }
        break;
    case DOCK_POS_RIGHT:
        strut_partial.top = TOPHEIGHT * devicePixelRatioF();
        strut_partial.top_start_x = primaryRect.x();
        strut_partial.top_end_x = primaryRect.x() + primaryRect.width();

        if (dockRect.bottomRight().y() + TOPHEIGHT >= primaryRect.height()) {
            setFixedSize(dockRect.topLeft().x(), TOPHEIGHT);
            m_mainPanel->resize(dockRect.topLeft().x(), TOPHEIGHT);
        }
        else {
            setFixedSize(primaryRect.width(), TOPHEIGHT);
            m_mainPanel->resize(primaryRect.width(), TOPHEIGHT);
        }

        move(primaryRect.x(), primaryRect.y());
        m_mainPanel->move(0, 0);
        break;
    case DOCK_POS_TOP:
        strut_partial.top = TOPHEIGHT * devicePixelRatioF() + dockRect.bottomRight().y();
        strut_partial.top_start_x = primaryRect.x();
        strut_partial.top_end_x = primaryRect.x() + primaryRect.width();

        move(primaryRect.x(), primaryRect.y() + dockRect.bottomRight().y());
        setFixedSize(primaryRect.width(), TOPHEIGHT);
        m_mainPanel->resize(primaryRect.width(), TOPHEIGHT);
        m_mainPanel->move(0, 0);
        break;
    default:
        break;
    }

    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winId(), strut_partial);

//    m_launchAni->setStartValue(QPoint(primaryRect.x(), primaryRect.y() - TOPHEIGHT));
//    m_launchAni->setEndValue(QPoint(primaryRect.x(), primaryRect.y()));

//    QTimer::singleShot(400, this, [=] {
//        m_launchAni->start();
//    });
}

void MainFrame::onWindowListChanged()
{
    QList<DForeignWindow*> windowList = DWindowManagerHelper::instance()->currentWorkspaceWindows();

    for (DForeignWindow * window : windowList) {
        if (window->winId() == this->window()->winId()) continue;

        connect(window, &DForeignWindow::windowStateChanged, this, &MainFrame::onWindowStateChanged, Qt::ConnectionType::UniqueConnection);
        window->windowStateChanged(window->windowState());
    }
}

//void MainFrame::updateWindowListInfo()
//{
//    if (m_infoUpdating) {
//        return;
//    }

//    // update info

//    m_infoUpdating= true;
//    bool isMaxWindow = false;

//    QMapIterator<WId, DForeignWindow*> map(m_windowList);
//    while (map.hasNext()) {
//        map.next();
//        DForeignWindow *w = map.value();

//        if (w->windowState() == Qt::WindowMaximized ||
//                (w->wmClass() != "dde-desktop" &&
//                 w->wmClass() != "deepin-topbar" &&
//                 w->position().y() <= 100 &&
//                 w->windowState() != Qt::WindowMinimized)) {

//            isMaxWindow = true;
//        }

//        if (w->wmClass() == "dde-launcher") {
//            if (m_mainPanel->pos() != QPoint(m_mainPanel->x(), -30)) {
//                m_hideWithLauncher->start();
//            }
//            m_infoUpdating = false;
//            return;
//        }

//        if (w->windowState() == Qt::WindowFullScreen) {
//            if (m_mainPanel->pos() != QPoint(m_mainPanel->x(), -30)) {
//                m_hideWithLauncher->start();
//            }
//            m_infoUpdating = false;
//            return;
//        }
//    }

//    if (isMaxWindow) {
//        m_mainPanel->setBackground(QColor(0, 0, 0, 255));
//    } else {
//    }

//    // if launcher hide
//    if (m_mainPanel->pos() == QPoint(m_mainPanel->x(), -30))
//        m_showWithLauncher->start();

//    m_infoUpdating = false;
//}

void MainFrame::onWindowStateChanged(Qt::WindowState windowState)
{
    DForeignWindow *w = qobject_cast<DForeignWindow*>(sender());
    Q_ASSERT(w);

    WId wid = w->winId();

    if (windowState == Qt::WindowMaximized) {
        if (!m_maxWindowList.contains(wid)) {
            m_maxWindowList << wid;
        }
    } else {
        if (m_maxWindowList.contains(wid)) {
            m_maxWindowList.removeOne(wid);
        }
    }

    if (m_maxWindowList.isEmpty()) {
        m_mainPanel->setBackground(QColor(0, 0, 0, 0));
    } else {
        m_mainPanel->setBackground(QColor(0, 0, 0, 255));
    }
}
