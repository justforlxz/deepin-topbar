#ifndef FRAMESHADOW_H
#define FRAMESHADOW_H

#include <QWidget>
#include <QDesktopWidget>
#include <QScreen>
#include <DPlatformWindowHandle>

DWIDGET_USE_NAMESPACE

class FrameShadow : public QWidget
{
    Q_OBJECT
public:
    explicit FrameShadow(QWidget *parent = nullptr);

private slots:
    void screenChanged();

private:
    DPlatformWindowHandle *m_handle;
};

#endif // FRAMESHADOW_H
