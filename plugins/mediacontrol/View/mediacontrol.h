#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QFrame>
#include <QLabel>

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
    QLabel *m_lastBtn;
    QLabel *m_previousBtn;
    QLabel *m_pauseBtn;
    PlayState m_playState;
};

#endif // MEDIACONTROL_H
