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

DWIDGET_USE_NAMESPACE

class MainFrame : public QFrame
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
    void updateWindowListInfo();

private:
    void init();
    void initConnect();
    void initAnimation();

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DBlurEffectWidget *m_blurEffectWidget;
    DPlatformWindowHandle *m_handle;
    QPropertyAnimation *m_launchAni;
    QPropertyAnimation *m_hideWithLauncher;
    QPropertyAnimation *m_showWithLauncher;
    QMap<WId,DForeignWindow*> m_windowList;
    bool m_infoUpdating;
};

#endif // MAINFRAME_H
