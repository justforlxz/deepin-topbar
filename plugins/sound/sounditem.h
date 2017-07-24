#ifndef SOUNDITEM_H
#define SOUNDITEM_H

#include "soundapplet.h"
#include "dbus/dbussink.h"
#include "fontlabel.h"
#include <QWidget>

class SoundItem : public QWidget
{
    Q_OBJECT

public:
    explicit SoundItem(QWidget *parent = 0);

    QWidget *popupApplet();

protected:
    void wheelEvent(QWheelEvent *e);

private slots:
    void refershIcon();
    void sinkChanged(DBusSink *sink);

private:
    FontLabel *m_fontLabel;
    SoundApplet *m_applet;
    DBusSink *m_sinkInter;
};

#endif // SOUNDITEM_H
