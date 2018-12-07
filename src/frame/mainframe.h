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
    void onWindowListChanged();
//    void updateWindowListInfo();
    void onWindowStateChanged(Qt::WindowState windowState);
    void delayedScreenChanged();

private:
    void init();
    void initConnect();
    void initAnimation();

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DPlatformWindowHandle *m_handle;
    QPropertyAnimation *m_launchAni;
//    QPropertyAnimation *m_hideWithLauncher;
//    QPropertyAnimation *m_showWithLauncher;
    DockInter *m_dockInter;

    QMap<WId,DForeignWindow*> m_windowList;
    QList<WId> m_windowIdList;
    QList<WId> m_maxWindowList;
};

#endif // MAINFRAME_H
