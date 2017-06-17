#include "frameshadow.h"
#include <QX11Info>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QApplication>

FrameShadow::FrameShadow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_handle = new DPlatformWindowHandle(this);
    m_handle->setBorderWidth(0);
    m_handle->setWindowRadius(0);

    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    screenChanged();

    QDesktopWidget *widget = QApplication::desktop();
    connect(widget, &QDesktopWidget::resized, this, &FrameShadow::screenChanged);
    connect(widget, &QDesktopWidget::primaryScreenChanged, this, &FrameShadow::screenChanged);
}

void FrameShadow::screenChanged()
{
    QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    resize(screen.width(), 25);
    move(screen.x(), 0);
}
