#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <QHBoxLayout>
#include <QDesktopWidget>

DWIDGET_USE_NAMESPACE

#define TOPHEIGHT 25

class MainFrame : public DBlurEffectWidget
{
    Q_OBJECT

public:
    MainFrame(QWidget *parent = 0);
    ~MainFrame();

private slots:
    void screenChanged();

private:
    QHBoxLayout *m_mainLayout;
    QDesktopWidget *m_desktopWidget;
};

#endif // WIDGET_H
