#include "mainframe.h"
#include "mainpanel.h"
#include <QScreen>
#include <QApplication>
#include <QRect>

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
    m_handle->setEnableSystemResize(true);

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
}
