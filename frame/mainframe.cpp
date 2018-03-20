#include "mainframe.h"

#include "utils/global.h"

#include <QScreen>
#include <QApplication>
#include <QRect>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>
#include <DPlatformWindowHandle>
#include <DForeignWindow>

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

MainFrame::MainFrame(QWidget *parent): QFrame(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    init();
    initAnimation();
    initConnect();
    screenChanged();

    connectWindowListChanged(this, [this] {
        QFunctionPointer wmClientList = Q_NULLPTR;

    #if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
        wmClientList = qApp->platformFunction(_getWindows);
    #endif

        if (wmClientList) {
            bool isMaxWindow = false;
            for (WId wid : reinterpret_cast<QVector<quint32>(*)()>(wmClientList)()) {
                if (DForeignWindow *w = DForeignWindow::fromWinId(wid)) {

                    if (w->windowState() == Qt::WindowMaximized) {
                        isMaxWindow = true;
                    }

                    if (w->wmClass() == "dde-launcher") {
                        if (m_mainPanel->pos() != QPoint(m_mainPanel->x(), -30)) {
                            m_hideWithLauncher->start();
                        }
                        return;
                    }

                    if (w->windowState() == Qt::WindowFullScreen) {
                        if (m_mainPanel->pos() != QPoint(m_mainPanel->x(), -30)) {
                            m_hideWithLauncher->start();
                        }
                        return;
                    }
                }
            }

            if (isMaxWindow) {
                m_mainPanel->setBackground(QColor(0, 0, 0, 255));
            } else {
                m_mainPanel->setBackground(QColor(0, 0, 0, 0));
            }
        }

        // if launcher hide
        if (m_mainPanel->pos() == QPoint(m_mainPanel->x(), -30))
            m_showWithLauncher->start();
    });
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
    m_blurEffectWidget->setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    m_blurEffectWidget->setMaskColor(DBlurEffectWidget::DarkColor);

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
}

void MainFrame::initConnect()
{
    connect(m_desktopWidget, &QDesktopWidget::resized, this, &MainFrame::screenChanged);
    connect(m_desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &MainFrame::screenChanged);
}

void MainFrame::initAnimation()
{
    m_launchAni = new QPropertyAnimation(this, "pos", this);
    m_launchAni->setDuration(1000);
    m_launchAni->setEasingCurve(QEasingCurve::OutBounce);

    connect(m_showWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
        m_blurEffectWidget->move(value.toPoint());
        m_blurEffectWidget->update();
    });

    connect(m_hideWithLauncher, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
        m_blurEffectWidget->move(value.toPoint());
        m_blurEffectWidget->update();
    });
}

void MainFrame::showSetting()
{
    QTimer::singleShot(1, m_mainPanel, &dtb::MainPanel::showSettingDialog);
}

void MainFrame::screenChanged()
{
    QRect screen = m_desktopWidget->screenGeometry(m_desktopWidget->primaryScreen());
    resize(screen.width(), TOPHEIGHT);
    m_mainPanel->resize(screen.width(), TOPHEIGHT);
    m_blurEffectWidget->resize(screen.width(), TOPHEIGHT);
    move(screen.x(), screen.y() - TOPHEIGHT);
    m_mainPanel->move(0, 0);
    m_blurEffectWidget->move(0, 0);

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

    strut_partial.top = TOPHEIGHT * devicePixelRatioF();
    strut_partial.top_start_x = screen.x();
    strut_partial.top_end_x = screen.x() + width() - 1;

    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winId(), strut_partial);

    m_launchAni->setStartValue(QPoint(screen.x(), screen.y() - TOPHEIGHT));
    m_launchAni->setEndValue(QPoint(screen.x(), screen.y()));

    QTimer::singleShot(400, this, [=] {
        m_launchAni->start();
    });
}
