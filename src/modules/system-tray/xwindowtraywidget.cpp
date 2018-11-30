/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "xwindowtraywidget.h"

#include <QWindow>
#include <QPainter>
#include <QX11Info>
#include <QDebug>
#include <QMouseEvent>
#include <QProcess>
#include <QThread>
#include <QApplication>
#include <QScreen>

#include <X11/extensions/shape.h>
#include <X11/extensions/XTest.h>
#include <X11/Xregion.h>

#include <xcb/composite.h>
#include <xcb/xcb_image.h>

static const qreal iconSize = 16;

#define DRAG_THRESHOLD  20

const QPoint rawXPosition(const QPoint &scaledPos)
{
    QRect g = qApp->primaryScreen()->geometry();
    for (auto *screen : qApp->screens())
    {
        const QRect &sg = screen->geometry();
        if (sg.contains(scaledPos))
        {
            g = sg;
            break;
        }
    }

    return g.topLeft() + (scaledPos - g.topLeft()) * qApp->devicePixelRatio();
}

void sni_cleanup_xcb_image(void *data)
{
    xcb_image_destroy(static_cast<xcb_image_t*>(data));
}

XWindowTrayWidget::XWindowTrayWidget(quint32 winId, QWidget *parent)
    : AbstractTrayWidget(parent),
      m_windowId(winId)
{
    wrapWindow();

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(100);
    m_updateTimer->setSingleShot(true);

    m_sendHoverEvent = new QTimer(this);
    m_sendHoverEvent->setInterval(100);
    m_sendHoverEvent->setSingleShot(true);

    connect(m_updateTimer, &QTimer::timeout, this, &XWindowTrayWidget::refershIconImage);
#ifdef DOCK_TRAY_USE_NATIVE_POPUP
    connect(m_sendHoverEvent, &QTimer::timeout, this, &XWindowTrayWidget::sendHoverEvent);
#endif

    setMouseTracking(true);

    m_updateTimer->start();
}

XWindowTrayWidget::~XWindowTrayWidget()
{
}

const QImage XWindowTrayWidget::trayImage()
{
    return m_image;
}

QSize XWindowTrayWidget::sizeHint() const
{
    return QSize(26, 26);
}

void XWindowTrayWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);

    m_updateTimer->start();
}

void XWindowTrayWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if (m_image.isNull())
        return m_updateTimer->start();

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
#ifdef QT_DEBUG
//    painter.fillRect(rect(), Qt::red);
#endif

    const QPoint p = rect().center() - m_image.rect().center() / m_image.devicePixelRatioF();
    painter.drawImage(p, m_image);

    painter.end();
}

void XWindowTrayWidget::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    const QPoint point(e->pos() - rect().center());
    if (point.manhattanLength() > 24)
        e->ignore();

    QWidget::mousePressEvent(e);
}

void XWindowTrayWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    m_sendHoverEvent->start();
}

void XWindowTrayWidget::configContainerPosition()
{
    auto c = QX11Info::connection();

    const QPoint p(rawXPosition(QCursor::pos()));

    const uint32_t containerVals[4] = {uint32_t(p.x()), uint32_t(p.y()), 1, 1};
    xcb_configure_window(c, m_containerWid,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y | XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                         containerVals);
    xcb_flush(c);
}

void XWindowTrayWidget::wrapWindow()
{
    auto c = QX11Info::connection();

    auto cookie = xcb_get_geometry(c, m_windowId);
    QScopedPointer<xcb_get_geometry_reply_t> clientGeom(xcb_get_geometry_reply(c, cookie, Q_NULLPTR));
    if (clientGeom.isNull())
        return;

    //create a container window
    const auto ratio = devicePixelRatioF();
    auto screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;
    m_containerWid = xcb_generate_id(c);
    uint32_t values[2];
    auto mask = XCB_CW_BACK_PIXEL | XCB_CW_OVERRIDE_REDIRECT;
    values[0] = ParentRelative; //draw a solid background so the embedded icon doesn't get garbage in it
    values[1] = true; //bypass wM
    xcb_create_window (c,                          /* connection    */
                       XCB_COPY_FROM_PARENT,          /* depth         */
                       m_containerWid,               /* window Id     */
                       screen->root,                 /* parent window */
                       0, 0,                         /* x, y          */
                       iconSize * ratio, iconSize * ratio,     /* width, height */
                       0,                            /* border_width  */
                       XCB_WINDOW_CLASS_INPUT_OUTPUT,/* class         */
                       screen->root_visual,          /* visual        */
                       mask, values);                /* masks         */

    /*
        We need the window to exist and be mapped otherwise the child won't render it's contents

        We also need it to exist in the right place to get the clicks working as GTK will check sendEvent locations to see if our window is in the right place. So even though our contents are drawn via compositing we still put this window in the right place

        We can't composite it away anything parented owned by the root window (apparently)
        Stack Under works in the non composited case, but it doesn't seem to work in kwin's composited case (probably need set relevant NETWM hint)

        As a last resort set opacity to 0 just to make sure this container never appears
    */
//    const uint32_t stackBelowData[] = {XCB_STACK_MODE_BELOW};
//    xcb_configure_window(c, m_containerWid, XCB_CONFIG_WINDOW_STACK_MODE, stackBelowData);

    QWindow * win = QWindow::fromWinId(m_containerWid);
    win->setOpacity(0);

//    setX11PassMouseEvent(true);

    xcb_flush(c);

    xcb_map_window(c, m_containerWid);

    xcb_reparent_window(c, m_windowId,
                        m_containerWid,
                        0, 0);

    /*
     * Render the embedded window offscreen
     */
    xcb_composite_redirect_window(c, m_windowId, XCB_COMPOSITE_REDIRECT_MANUAL);


    /* we grab the window, but also make sure it's automatically reparented back
     * to the root window if we should die.
    */
    xcb_change_save_set(c, XCB_SET_MODE_INSERT, m_windowId);

    //tell client we're embedding it
    // xembed_message_send(m_windowId, XEMBED_EMBEDDED_NOTIFY, m_containerWid, 0, 0);

    //move window we're embedding
    /*
    const uint32_t windowMoveConfigVals[2] = { 0, 0 };
    xcb_configure_window(c, m_windowId,
                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
                         windowMoveCentially quitting the application. Returns onfigVals);
    */

    //if the window is a clearly stupid size resize to be something sensible
    //this is needed as chormium and such when resized just fill the icon with transparent space and only draw in the middle
    //however spotify does need this as by default the window size is 900px wide.
    //use an artbitrary heuristic to make sure icons are always sensible
//    if (clientGeom->width > iconSize || clientGeom->height > iconSize )
    {
        const uint32_t windowMoveConfigVals[2] = { uint32_t(iconSize * ratio), uint32_t(iconSize * ratio) };
        xcb_configure_window(c, m_windowId,
                             XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
                             windowMoveConfigVals);
    }

    //show the embedded window otherwise nothing happens
    xcb_map_window(c, m_windowId);

//    xcb_clear_area(c, 0, m_windowId, 0, 0, qMin(clientGeom->width, iconSize), qMin(clientGeom->height, iconSize));

    xcb_flush(c);
//    setWindowOnTop(false);
    setWindowOnTop(true);
    setX11PassMouseEvent(true);
}

void XWindowTrayWidget::sendHoverEvent()
{
    // fake enter event
    const QPoint p(rawXPosition(QCursor::pos()));
    configContainerPosition();
    setX11PassMouseEvent(false);
    setWindowOnTop(true);
    XTestFakeMotionEvent(QX11Info::display(), 0, p.x(), p.y(), CurrentTime);
    XFlush(QX11Info::display());
    QTimer::singleShot(100, this, [=] { setX11PassMouseEvent(true); });
}

void XWindowTrayWidget::updateIcon()
{
    if (!isVisible() && !m_active)
        return;

    m_updateTimer->start();
}

//void TrayWidget::hideIcon()
//{
//    auto c = QX11Info::connection();

//    const uint32_t stackAboveData[] = {XCB_STACK_MODE_BELOW};
//    xcb_configure_window(c, m_containerWid, XCB_CONFIG_WINDOW_STACK_MODE, stackAboveData);

//    const uint32_t windowMoveConfigVals[2] = {0, 0};
//    xcb_configure_window(c, m_containerWid,
//                         XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,
//                         windowMoveConfigVals);

//    hide();
//}

void XWindowTrayWidget::sendClick(uint8_t mouseButton, int x, int y)
{
    if (isBadWindow())
        return;

    m_sendHoverEvent->stop();

    const QPoint p(rawXPosition(QPoint(x, y)));
    configContainerPosition();
    setX11PassMouseEvent(false);
    setWindowOnTop(true);
    XTestFakeMotionEvent(QX11Info::display(), 0, p.x(), p.y(), CurrentTime);
    XFlush(QX11Info::display());
    XTestFakeButtonEvent(QX11Info::display(), mouseButton, true, CurrentTime);
    XFlush(QX11Info::display());
    XTestFakeButtonEvent(QX11Info::display(), mouseButton, false, CurrentTime);
    XFlush(QX11Info::display());
    QTimer::singleShot(100, this, [=] { setX11PassMouseEvent(true); });
}

void XWindowTrayWidget::setActive(const bool active)
{
    m_active = active;
    m_updateTimer->start();
}

void XWindowTrayWidget::refershIconImage()
{
    const auto ratio = devicePixelRatioF();
    auto c = QX11Info::connection();
    auto cookie = xcb_get_geometry(c, m_windowId);
    QScopedPointer<xcb_get_geometry_reply_t> geom(xcb_get_geometry_reply(c, cookie, Q_NULLPTR));
    if (geom.isNull())
        return;

    xcb_expose_event_t expose;
    expose.response_type = XCB_EXPOSE;
    expose.window = m_containerWid;
    expose.x = 0;
    expose.y = 0;
    expose.width = iconSize * ratio;
    expose.height = iconSize * ratio;
    xcb_send_event_checked(c, false, m_containerWid, XCB_EVENT_MASK_VISIBILITY_CHANGE, reinterpret_cast<char *>(&expose));
    xcb_flush(c);

    xcb_image_t *image = xcb_image_get(c, m_windowId, 0, 0, geom->width, geom->height, ~0, XCB_IMAGE_FORMAT_Z_PIXMAP);
    if (!image)
        return;

    QImage qimage(image->data, image->width, image->height, image->stride, QImage::Format_ARGB32, sni_cleanup_xcb_image, image);
    if (qimage.isNull())
        return;

    m_image = qimage.scaled(16 * ratio, 16 * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_image.setDevicePixelRatio(ratio);

    update();
    emit iconChanged();
}

void XWindowTrayWidget::setX11PassMouseEvent(const bool pass)
{
    if (pass)
    {
        XShapeCombineRectangles(QX11Info::display(), m_containerWid, ShapeBounding, 0, 0, nullptr, 0, ShapeSet, YXBanded);
        XShapeCombineRectangles(QX11Info::display(), m_containerWid, ShapeInput, 0, 0, nullptr, 0, ShapeSet, YXBanded);
    }
    else
    {
        XRectangle rectangle;
        rectangle.x = 0;
        rectangle.y = 0;
        rectangle.width = 1;
        rectangle.height = 1;

        XShapeCombineRectangles(QX11Info::display(), m_containerWid, ShapeBounding, 0, 0, &rectangle, 1, ShapeSet, YXBanded);
        XShapeCombineRectangles(QX11Info::display(), m_containerWid, ShapeInput, 0, 0, &rectangle, 1, ShapeSet, YXBanded);
    }

    XFlush(QX11Info::display());
}

void XWindowTrayWidget::setWindowOnTop(const bool top)
{
    auto c = QX11Info::connection();
    const uint32_t stackAboveData[] = {top ? XCB_STACK_MODE_ABOVE : XCB_STACK_MODE_BELOW};
    xcb_configure_window(c, m_containerWid, XCB_CONFIG_WINDOW_STACK_MODE, stackAboveData);
    xcb_flush(c);
}

bool XWindowTrayWidget::isBadWindow()
{
    auto c = QX11Info::connection();

    auto cookie = xcb_get_geometry(c, m_windowId);
    QScopedPointer<xcb_get_geometry_reply_t> clientGeom(xcb_get_geometry_reply(c, cookie, Q_NULLPTR));
    return clientGeom.isNull();
}
