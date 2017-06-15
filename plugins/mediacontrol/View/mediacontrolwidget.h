#ifndef MEDIACONTROLWIDGET_H
#define MEDIACONTROLWIDGET_H

#include "mediacontrol.h"
#include "DBus/dbusmediaplayer2.h"
#include <QFrame>
#include <QLabel>
#include <QPropertyAnimation>

class MediaControlWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MediaControlWidget(QWidget *parent = nullptr);
    void initMpris();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private:
    MediaControl *m_mediaControl;
    DBusMediaPlayer2 *m_mediaInter;
    QLabel *m_mediaTitle;
    QPropertyAnimation *m_hoverControlAni;
    QPropertyAnimation *m_showControlAni;
};

#endif // MEDIACONTROLWIDGET_H
