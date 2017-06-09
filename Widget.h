#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <DBlurEffectWidget>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class Widget : public DBlurEffectWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QHBoxLayout *m_mainLayout;
};

#endif // WIDGET_H
