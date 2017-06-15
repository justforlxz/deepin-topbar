#ifndef FRAME_H
#define FRAME_H

#include <QWidget>
#include <DBlurEffectWidget>

DWIDGET_USE_NAMESPACE

class Frame : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);

public slots:
    void registerDesktop();

};

#endif // FRAME_H
