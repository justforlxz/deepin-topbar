#include "mainframe.h"
#include "topbar.h"
#include "xcb-misc/XcbMisc.h"
#include <X11/X.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>
#include <DPlatformWindowHandle>

MainFrame::MainFrame(QWidget *parent)
    : DBlurEffectWidget(parent),
      m_mainLayout(new QHBoxLayout)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    setBlendMode(InWindowBlend);
    setMaskColor(DBlurEffectWidget::LightColor);

    DPlatformWindowHandle *handle = new DPlatformWindowHandle(this);
    handle->setTranslucentBackground(true);
    handle->setWindowRadius(0);
    handle->setBorderWidth(0);
    handle->setEnableSystemResize(false);

    move(0, 0);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();

    resize(screen.width(), 20);

    //register type to Dock
    XcbMisc * xcb = XcbMisc::instance();
    xcb->set_window_type(winId(), XcbMisc::Dock);

    xcb->clear_strut_partial(winId());

    XcbMisc::Orientation orientation = XcbMisc::OrientationTop;
    uint strut = 0;
    uint strutStart = 0;
    uint strutEnd = 0;

    const QPoint p(0, 0);
    const QRect r = QRect(p, size());

    orientation = XcbMisc::OrientationTop;
    strut = r.bottom() + 1;
    strutStart = r.left();
    strutEnd = r.right();

    xcb->set_strut_partial(winId(), orientation, strut, strutStart, strutEnd);

    // Don't keep out launcher
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    lower();

    TopBar *bar = new TopBar;
    m_mainLayout->addWidget(bar);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);
}

MainFrame::~MainFrame()
{

}
