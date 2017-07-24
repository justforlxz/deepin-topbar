#ifndef SOUNDITEM_H
#define SOUNDITEM_H

#include "soundapplet.h"
#include "dbus/dbussink.h"

#include <QWidget>

class SoundItem : public QWidget
{
    Q_OBJECT

public:
    explicit SoundItem(QWidget *parent = 0);

    QWidget *tipsWidget();
    QWidget *popupApplet();

    const QString contextMenu() const;
    void invokeMenuItem(const QString menuId, const bool checked);

signals:
    void requestContextMenu() const;

protected:
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void paintEvent(QPaintEvent *e);

private slots:
    void refershIcon();
    void refershTips(const bool force = false);
    void sinkChanged(DBusSink *sink);

private:
    QLabel *m_tipsLabel;
    SoundApplet *m_applet;
    DBusSink *m_sinkInter;
    QPixmap m_iconPixmap;
};

#endif // SOUNDITEM_H
