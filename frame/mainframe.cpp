#include "mainframe.h"
#include "mainpanel.h"
#include <QScreen>
#include <QApplication>
#include <QRect>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>

DWIDGET_USE_NAMESPACE

MainFrame::MainFrame(QWidget *parent): QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowStaysOnBottomHint);
    setAttribute(Qt::WA_TranslucentBackground);

    init();
    initAnimation();
    screenChanged();
    initConnect();
}

MainFrame::~MainFrame()
{
    m_desktopWidget->deleteLater();
}

/*
     Think zccrs, Perfect protection against launcher. It won't stop launcher at last.
     */

void MainFrame::init()
{
    m_desktopWidget = QApplication::desktop();

    m_blurEffectWidget = new DBlurEffectWidget(this);
    m_blurEffectWidget->setBlendMode(DBlurEffectWidget::BehindWindowBlend);
    m_blurEffectWidget->setMaskColor(DBlurEffectWidget::LightColor);
    m_blurEffectWidget->setWindowFlags(Qt::WindowDoesNotAcceptFocus);

    m_handle = new DPlatformWindowHandle(this);
    m_handle->setBorderWidth(0);
    m_handle->setWindowRadius(0);
    m_handle->setEnableSystemMove(true);
    m_handle->setEnableSystemResize(false);

    m_mainPanel = new MainPanel(this);
}

void MainFrame::initConnect()
{
    connect(m_desktopWidget, &QDesktopWidget::resized, this, &MainFrame::screenChanged);
    connect(m_desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &MainFrame::screenChanged);
}

void MainFrame::initAnimation()
{

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

    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[2];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DOCK;
    atoms[1] = m_ewmh_connection._NET_WM_STATE_BELOW;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    xcb_ewmh_wm_strut_partial_t strutPartial;
    memset(&strutPartial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    // clear strut partial
    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winId(), strutPartial);

    // set strct partial
    xcb_ewmh_wm_strut_partial_t strut_partial;
    memset(&strut_partial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    strut_partial.top = TOPHEIGHT * devicePixelRatioF();
    strut_partial.top_start_x = x();
    strut_partial.top_end_x = width();

    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winId(), strut_partial);
}
