#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QFrame>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <DBlurEffectWidget>
#include <QPropertyAnimation>

DWIDGET_USE_NAMESPACE

#define TOPHEIGHT 25

class MainPanel;

class MainFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void registerDesktop();

    void init();
    void initConnect();
    void initAnimation();

private slots:
    void screenChanged();

private:
    QDesktopWidget *m_desktopWidget;
    MainPanel *m_mainPanel;
    DBlurEffectWidget *m_blurEffectWidget;
    QPropertyAnimation *m_hideWithLauncher;
    QPropertyAnimation *m_showWithLauncher;
};

#endif // MAINFRAME_H
