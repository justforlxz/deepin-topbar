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

public slots:
    void screenChanged();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    DPlatformWindowHandle *m_handle;
};

#endif // FRAMESHADOW_H
