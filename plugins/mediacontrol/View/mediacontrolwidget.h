#ifndef MEDIACONTROLWIDGET_H
#define MEDIACONTROLWIDGET_H

#include "mediacontrol.h"
#include "DBus/dbusmediaplayer2.h"
#include <QWidget>

class MediaControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MediaControlWidget(QWidget *parent = nullptr);
    void initMpris();

private:
    MediaControl *m_mediaControl;
    DBusMediaPlayer2 *m_mediaInter;
};

#endif // MEDIACONTROLWIDGET_H
