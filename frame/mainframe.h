#ifndef WIDGET_H
#define WIDGET_H

#include <QFrame>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QPropertyAnimation>
#include <DPlatformWindowHandle>
#include <DBlurEffectWidget>
//dbus
#include <com_deepin_dde_launcher.h>

using LauncherInter = com::deepin::dde::Launcher;

DWIDGET_USE_NAMESPACE

#define TOPHEIGHT 25

class MainPanel;

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void init();
    void initConnect();
    void initAnimation();

private slots:
    void screenChanged();

private:
    QDesktopWidget *m_desktopWidget;
    DBlurEffectWidget *m_blurEffectWidget;
    MainPanel *m_mainPanel;
    LauncherInter *m_launcherInter;
    QPropertyAnimation *m_hideWithLauncher;
    QPropertyAnimation *m_showWithLauncher;
};

#endif // WIDGET_H
