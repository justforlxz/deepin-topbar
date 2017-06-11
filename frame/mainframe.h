#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class MainFrame : public DBlurEffectWidget
{
    Q_OBJECT

public:
    MainFrame(QWidget *parent = 0);
    ~MainFrame();

private:
    QHBoxLayout *m_mainLayout;
};

#endif // WIDGET_H
