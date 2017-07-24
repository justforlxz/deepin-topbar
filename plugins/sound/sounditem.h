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
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private slots:
    void refershIcon();
    void sinkChanged(DBusSink *sink);

private:
    FontLabel *m_fontLabel;
    SoundApplet *m_applet;
    DBusSink *m_sinkInter;
    bool m_isEnter = false;
};

#endif // SOUNDITEM_H
