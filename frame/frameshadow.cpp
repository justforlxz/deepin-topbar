#include "frameshadow.h"
#include <QApplication>

FrameShadow::FrameShadow(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(
                Qt::FramelessWindowHint |
                Qt::WindowDoesNotAcceptFocus |
                Qt::WindowStaysOnBottomHint
                );

    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);

    m_handle = new DPlatformWindowHandle(this);
    m_handle->setBorderWidth(0);
    m_handle->setWindowRadius(0);
    m_handle->setEnableSystemMove(true);
    m_handle->setEnableSystemResize(true);

    QDesktopWidget *widget = QApplication::desktop();
    connect(widget, &QDesktopWidget::resized, this, &FrameShadow::screenChanged);
    connect(widget, &QDesktopWidget::primaryScreenChanged, this, &FrameShadow::screenChanged);
}

void FrameShadow::screenChanged()
{
    QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    setFixedSize(screen.width(), 28);
    move(screen.x(), screen.y());
}
