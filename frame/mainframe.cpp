#include "mainframe.h"
#include "topbar.h"
#include "xcb-misc/XcbMisc.h"
#include <X11/X.h>
#include <X11/Xutil.h>
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
    handle->setShadowOffset(QPoint(0, -5));

    move(0, 0);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();

    resize(screen.width(), 20);

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

    TopBar *bar = new TopBar;
    m_mainLayout->addWidget(bar);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);
}

MainFrame::~MainFrame()
{

}
