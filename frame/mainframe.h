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

#include "mainpanel.h"

DWIDGET_USE_NAMESPACE

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

private slots:
    void screenChanged();

private:
    void init();
    void initConnect();
    void initAnimation();
    void setTheme(const QString &key);

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DBlurEffectWidget *m_blurEffectWidget;
    DPlatformWindowHandle *m_handle;
    QGSettings *m_gsettings;
    QPropertyAnimation *m_launchAni;
};

#endif // MAINFRAME_H
