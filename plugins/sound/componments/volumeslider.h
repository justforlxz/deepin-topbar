#ifndef VOLUMESLIDER_H
#define VOLUMESLIDER_H

#include <QSlider>
#include <QTimer>

class VolumeSlider : public QSlider
{
    Q_OBJECT

public:
    explicit VolumeSlider(QWidget *parent = 0);

    void setValue(const int value);

signals:
    void requestPlaySoundEffect() const;

protected:
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;

private slots:
    void onTimeout();

private:
    bool m_pressed;
    QTimer *m_timer;
};

#endif // VOLUMESLIDER_H
