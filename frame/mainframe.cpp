#include "mainframe.h"
#include "mainpanel.h"
#include "xcb-misc/XcbMisc.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <QApplication>
#include <QRect>
#include <QTimer>

MainFrame::MainFrame(QWidget *parent): QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedHeight(TOPHEIGHT);

    init();
    initAnimation();
    initConnect();

    screenChanged();
    connect(m_desktopWidget, &QDesktopWidget::resized, this, &MainFrame::screenChanged);

}

MainFrame::~MainFrame()
{
    m_desktopWidget->deleteLater();
}

void MainFrame::init()
{
    m_desktopWidget = QApplication::desktop();

    m_blurEffectWidget = new DBlurEffectWidget(this);
    m_blurEffectWidget->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    m_blurEffectWidget->setMaskColor(DBlurEffectWidget::LightColor);
    m_blurEffectWidget->lower();

    m_mainPanel = new MainPanel(this);

    // I can't handle it properly. unable keep out launcher

//    m_launcherInter = new LauncherInter("com.deepin.dde.Launcher",
//                                        "/com/deepin/dde/Launcher",
//                                        QDBusConnection::sessionBus(),
//                                        this);
}

void MainFrame::initConnect()
{
//    connect(m_launcherInter, &LauncherInter::Shown, this, [=]{
//        m_hideWithLauncher->start();
//    });

//    connect(m_launcherInter, &LauncherInter::Closed, this, [=]{
//        m_showWithLauncher->start();
//    });

//    connect(m_showWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
//        m_blurEffectWidget->move(value.toPoint());
//    });

//    connect(m_hideWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
//        m_blurEffectWidget->move(value.toPoint());
//    });

//    connect(m_showWithLauncher, &QPropertyAnimation::finished, this, [=]{
//    });

//    connect(m_hideWithLauncher, &QPropertyAnimation::finished, this, [=]{

//    });
}

void MainFrame::initAnimation()
{
//    m_showWithLauncher =new QPropertyAnimation(m_mainPanel, "pos", m_mainPanel);
//    m_showWithLauncher->setDuration(300);
//    m_showWithLauncher->setStartValue(QPoint(m_mainPanel->x(), -m_mainPanel->height()));
//    m_showWithLauncher->setEndValue(QPoint(m_mainPanel->x(), 0));
//    m_showWithLauncher->setEasingCurve(QEasingCurve::InOutCubic);

//    m_hideWithLauncher =new QPropertyAnimation(m_mainPanel, "pos", m_mainPanel);
//    m_hideWithLauncher->setDuration(300);
//    m_hideWithLauncher->setStartValue(QPoint(m_mainPanel->x(), 0));
//    m_hideWithLauncher->setEndValue(QPoint(m_mainPanel->x(), -m_mainPanel->height()));
//    m_hideWithLauncher->setEasingCurve(QEasingCurve::InOutCubic);
}

void MainFrame::screenChanged()
{
    QRect screen = m_desktopWidget->screenGeometry(m_desktopWidget->primaryScreen());
    resize(screen.width(), TOPHEIGHT);
    m_mainPanel->resize(screen.width(), TOPHEIGHT);
    m_blurEffectWidget->resize(screen.width(), TOPHEIGHT);
    move(screen.x(), 0);
    m_mainPanel->move(0, 0);
    m_blurEffectWidget->move(0, 0);

    //register type to Dock

    XcbMisc * xcb = XcbMisc::instance();
    xcb->clear_strut_partial(winId());

    XcbMisc::Orientation orientation = XcbMisc::OrientationTop;
    uint strut = 0;
    uint strutStart = 0;
    uint strutEnd = 0;

    const QPoint p(screen.x(), 0);
    const QRect r = QRect(p, size());

    orientation = XcbMisc::OrientationTop;
    strut = r.bottom() + 2;
    strutStart = r.left();
    strutEnd = r.right();

    xcb->set_strut_partial(winId(), orientation, strut, strutStart, strutEnd);
    xcb->set_window_type(winId(), XcbMisc::Dock);
}
