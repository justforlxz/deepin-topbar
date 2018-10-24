#include "mainframe.h"

#include "utils/global.h"

#include <QScreen>
#include <QApplication>
#include <QRect>
#include <QtX11Extras/QX11Info>
#include <DPlatformWindowHandle>
#include <DForeignWindow>
#include <QTimer>
#include <dbusdock.h>
#include "utils/xcb_misc.h"

DWIDGET_USE_NAMESPACE

#define DEFINE_CONST_CHAR(Name) const char _##Name[] = "_d_" #Name

// functions
DEFINE_CONST_CHAR(getWindows);
DEFINE_CONST_CHAR(connectWindowListChanged);

static bool connectWindowListChanged(QObject *object, std::function<void ()> slot)
{
    QFunctionPointer connectWindowListChanged = Q_NULLPTR;

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    connectWindowListChanged = qApp->platformFunction(_connectWindowListChanged);
#endif

    return connectWindowListChanged && reinterpret_cast<bool(*)(QObject *object, std::function<void ()>)>(connectWindowListChanged)(object, slot);
}

MainFrame::MainFrame(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    init();
    initAnimation();
    initConnect();
    screenChanged();

    connectWindowListChanged(this, [=] {
        onWindowListChanged();
    });

    onWindowListChanged();
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

    m_dockInter = new DBusDock("com.deepin.dde.daemon.Dock","/com/deepin/dde/daemon/Dock" , QDBusConnection::sessionBus(),this);
}

void MainFrame::initConnect()
{
    connect(m_desktopWidget, &QDesktopWidget::resized, this, &MainFrame::screenChanged);
    connect(m_desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &MainFrame::screenChanged);

    connect(m_dockInter, &DBusDock::DisplayModeChanged, this, &MainFrame::delayedScreenChanged);
    connect(m_dockInter, &DBusDock::HideModeChanged, this, &MainFrame::delayedScreenChanged);
    connect(m_dockInter, &DBusDock::PositionChanged, this, &MainFrame::delayedScreenChanged);
    connect(m_dockInter, &DBusDock::IconSizeChanged, this, &MainFrame::delayedScreenChanged);
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

void MainFrame::setDocked(bool value)
{
    XcbMisc::instance()->set_window_type(winId(), value ? XcbMisc::Dock : XcbMisc::Normal);
}

void MainFrame::clearScreenGeometry()
{
    XcbMisc::instance()->set_strut_partial(winId(), XcbMisc::OrientationTop, 0, 0, 0);
}

void MainFrame::reserveScreenGeometry(int top, int startX, int endX)
{
    XcbMisc::instance()->set_strut_partial(winId(), XcbMisc::OrientationTop, top, startX, endX);
}

void MainFrame::delayedScreenChanged()
{
    setDocked(false);
    clearScreenGeometry();

    // delay is required so that screen
    // available geometry is updated
    // after dock size/position update
    QTimer::singleShot(1000, [this](){ resizeWindow(false); });    
}

void MainFrame::resizeWindow(bool hidden)
{
    QRect screen = m_desktopWidget->availableGeometry(m_desktopWidget->primaryScreen());

    resize(screen.width(), TOPHEIGHT);
    m_mainPanel->resize(screen.width(), TOPHEIGHT);
    resize(screen.width(), TOPHEIGHT);
    move(screen.x(), screen.y() - (hidden ? TOPHEIGHT : 0));
    m_mainPanel->move(0, 0);

    setDocked(true);
    reserveScreenGeometry((screen.y() + TOPHEIGHT) * devicePixelRatioF(), screen.x(), screen.x() + width() - 1);


    m_launchAni->setStartValue(QPoint(x(), y()));
    m_launchAni->setEndValue(QPoint(x(), y() + (hidden ? TOPHEIGHT : 0)));

    QTimer::singleShot(400, this, [=] {
        m_launchAni->start();
    });
}

void MainFrame::screenChanged()
{
    resizeWindow(true);
}

void MainFrame::onWindowListChanged()
{
    QFunctionPointer wmClientList = Q_NULLPTR;

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    wmClientList = qApp->platformFunction(_getWindows);
#endif

    if (wmClientList) {
        QList<WId> newList;
        // create new DForeignWindow
        for (WId wid : reinterpret_cast<QVector<quint32>(*)()>(wmClientList)()) {
            if (wid == this->topLevelWidget()->internalWinId()) {
                continue;
            }

            newList << wid;

            if (!m_windowList.keys().contains(wid)) {
                DForeignWindow *w = DForeignWindow::fromWinId(wid);
                if (!w) {
                    continue;
                }

                connect(w, &DForeignWindow::windowStateChanged, this, &MainFrame::onWindowStateChanged);
                w->windowStateChanged(w->windowState());

                m_windowList[wid] = w;
                m_windowIdList << wid;
            }
        }
        // remove old DForeignWindow
        QMapIterator<WId,DForeignWindow*> map(m_windowList);
        while (map.hasNext()) {
            map.next();
            if (!newList.contains(map.key())) {
                map.value()->deleteLater();
                if (m_maxWindowList.contains(map.key())) {
                    m_maxWindowList.removeOne(map.key());
                }
                m_windowList.remove(map.key());
            }
        }
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
