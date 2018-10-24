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

#include "mainpanel.h"

class DBusDock;

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

    void setDocked(bool value);
    void reserveScreenGeometry(int top, int startX, int endX);
    void clearScreenGeometry();
    void resizeWindow(bool hidden);

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DPlatformWindowHandle *m_handle;
    QPropertyAnimation *m_launchAni;
    QPropertyAnimation *m_hideWithLauncher;
    QPropertyAnimation *m_showWithLauncher;
    QMap<WId,DForeignWindow*> m_windowList;
    QList<WId> m_windowIdList;
    QList<WId> m_maxWindowList;

    DBusDock *m_dockInter;
};

#endif // MAINFRAME_H
