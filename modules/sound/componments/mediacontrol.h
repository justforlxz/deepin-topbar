#ifndef MEDIACONTROL_H
#define MEDIACONTROL_H

#include <QFrame>
#include <QLabel>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

namespace dtb {
namespace widgets {
class FontLabel;
}

namespace sound {
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

    QWidget *createWidget(QWidget *parent);

signals:
    void requestPrevious();
    void requestLast();
    void requestPause();

public slots:
    void setPlayState(PlayState state);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    widgets::FontLabel *m_lastBtn;
    widgets::FontLabel *m_previousBtn;
    widgets::FontLabel *m_pauseBtn;
    PlayState m_playState;
};
}
}

#endif // MEDIACONTROL_H
