#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <DBlurEffectWidget>
#include <QPropertyAnimation>
#include <DPlatformWindowHandle>

#include "mainpanel.h"

DWIDGET_USE_NAMESPACE

#define TOPHEIGHT 28

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

private:
    QDesktopWidget *m_desktopWidget;
    dtb::MainPanel *m_mainPanel;
    DBlurEffectWidget *m_blurEffectWidget;
    DPlatformWindowHandle *m_handle;
};

#endif // MAINFRAME_H
