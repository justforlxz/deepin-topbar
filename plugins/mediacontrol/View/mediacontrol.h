#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QFrame>
#include <QLabel>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

namespace Plugin {
namespace MediaControl {
class MediaControl : public QFrame
{
    Q_OBJECT
public:
    explicit MediaControl(QWidget *parent = 0);

    enum PlayState {
        Play,
        Pause,
        Stop,
        Last,
        Previous
    };

signals:
    void requestPrevious();
    void requestLast();
    void requestPause();

public slots:
    void setPlayState(PlayState state);

private:
    DImageButton *m_lastBtn;
    DImageButton *m_previousBtn;
    DImageButton *m_pauseBtn;
    PlayState m_playState;
};
}
}




#endif // MEDIACONTROL_H
