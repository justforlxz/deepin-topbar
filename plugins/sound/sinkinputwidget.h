#ifndef SINKINPUTWIDGET_H
#define SINKINPUTWIDGET_H

#include "dbus/dbussinkinput.h"
#include "componments/volumeslider.h"

#include <QFrame>

#include <dimagebutton.h>
#include <QPainter>

class SinkInputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SinkInputWidget(const QString &inputPath, QWidget *parent = 0);

private slots:
    void setVolume(const int value);
    void setMute();
    void setMuteIcon();
    void onPlaySoundEffect();

private:
    DBusSinkInput *m_inputInter;

    Dtk::Widget::DImageButton *m_volumeIcon;
    VolumeSlider *m_volumeSlider;
};

#endif // SINKINPUTWIDGET_H
