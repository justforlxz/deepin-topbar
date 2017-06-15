#ifndef MEDIACONTROLWIDGET_H
#define MEDIACONTROLWIDGET_H

#include "mediacontrol.h"
#include "DBus/dbusmediaplayer2.h"
#include <QFrame>
#include <QLabel>

class MediaControlWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MediaControlWidget(QWidget *parent = nullptr);
    void initMpris();

private:
    MediaControl *m_mediaControl;
    DBusMediaPlayer2 *m_mediaInter;
    QLabel *m_mediaTitle;
};

#endif // MEDIACONTROLWIDGET_H
