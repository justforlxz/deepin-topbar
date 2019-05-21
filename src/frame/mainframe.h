#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <DBlurEffectWidget>
#include <QPropertyAnimation>
#include <DPlatformWindowHandle>
#include <QPropertyAnimation>
#include <DForeignWindow>
#include <com_deepin_dde_daemon_dock.h>
#include <memory>

#include "mainpanel.h"

using DockInter = com::deepin::dde::daemon::Dock;

DWIDGET_USE_NAMESPACE

class MainFrame : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

public slots:
    void showSetting();

private slots:
    void screenChanged();
#if (DTK_VERSION >= DTK_VERSION_CHECK(2, 0, 9, 10))
    void onWindowListChanged();
#endif
    void onWindowStateChanged(Qt::WindowState windowState);
    void delayedScreenChanged();

private:
    void init();
    void initConnect();
    void initAnimation();
    void onWindowPosChanged(DForeignWindow *window);
    void updateBackground();
    void updateBorderPath();
    void setBackground(const QColor &color);
    void onBackgroundChanged(const QColor &color);
    QPainterPath pathHandle() const;

#ifdef ENABLE_RATOTE
    bool isRotated() const;
#endif

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DPlatformWindowHandle *m_handle;
    QPropertyAnimation *m_launchAni;
//    QPropertyAnimation *m_hideWithLauncher;
//    QPropertyAnimation *m_showWithLauncher;
    DockInter *m_dockInter;
    QWidget *m_structWidget;

    QMap<WId,DForeignWindow*> m_windowList;
    QList<WId> m_windowIdList;
    QList<WId> m_maxWindowList;
    QList<WId> m_overlapping;
    QList<WId> m_fullWindowList;
    QVariantAnimation *m_backgroundAni;
    QColor m_defaultBgColor;
    QColor m_backgroundColor;
};

#endif // MAINFRAME_H
