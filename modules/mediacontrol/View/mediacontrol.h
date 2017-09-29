#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QFrame>
#include <QLabel>
#include <dimagebutton.h>
#include "fontlabel.h"

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

    protected:
        bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

    private:
        FontLabel *m_lastBtn;
        FontLabel *m_previousBtn;
        FontLabel *m_pauseBtn;
        PlayState m_playState;
    };
    }
}




#endif // MEDIACONTROL_H
