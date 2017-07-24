#ifndef SOUNDAPPLET_H
#define SOUNDAPPLET_H

#include "componments/volumeslider.h"
#include "dbus/dbusaudio.h"
#include "dbus/dbussink.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QGSettings>
#include <dimagebutton.h>

class SoundApplet : public QScrollArea
{
    Q_OBJECT

public:
    explicit SoundApplet(QWidget *parent = 0);

    int volumeValue() const;
    VolumeSlider *mainSlider();

signals:
    void volumeChanged(const int value) const;
    void defaultSinkChanged(DBusSink *sink) const;

private slots:
    void defaultSinkChanged();
    void onVolumeChanged();
    void volumeSliderValueChanged();
    void sinkInputsChanged();
    void toggleMute();
    void delayLoad();
    void onPlaySoundEffect();

private:
    QWidget *m_centralWidget;
    QWidget *m_applicationTitle;
    Dtk::Widget::DImageButton *m_volumeBtn;
    VolumeSlider *m_volumeSlider;
    QVBoxLayout *m_centralLayout;

    DBusAudio *m_audioInter;
    DBusSink *m_defSinkInter;
    QGSettings *m_gsetting;
};

#endif // SOUNDAPPLET_H
