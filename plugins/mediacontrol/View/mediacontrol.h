#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QFrame>

#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

class MediaControl : public QFrame
{
    Q_OBJECT
public:
    explicit MediaControl(QWidget *parent = 0);

signals:
    void requestPrevious();
    void requestLast();
    void requestPause();

private:
    DImageButton *m_lastBtn;
    DImageButton *m_previousBtn;
    DImageButton *m_pauseBtn;
};

#endif // MEDIACONTROL_H
