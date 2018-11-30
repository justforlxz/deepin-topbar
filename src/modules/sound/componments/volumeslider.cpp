#include "volumeslider.h"

#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

using namespace dtb;
using namespace dtb::sound;

VolumeSlider::VolumeSlider(QWidget *parent)
    : QSlider(Qt::Horizontal, parent),
      m_pressed(false),
      m_timer(new QTimer(this))
{
    setMinimum(0);
    setMaximum(1000);
    setTickInterval(50);
    setPageStep(50);
    setTickPosition(QSlider::NoTicks);
    setFixedHeight(22);
    setStyleSheet("QSlider::groove:horizontal,QSlider::add-page:horizontal{"
                  "height: 3px;"
                  "border-radius: 3px;"
                  "background: #18181a;"
                  "}"
                  "QSlider::sub-page:horizontal{"
                  "height: 8px;"
                  "border-radius: 3px;"
                  "background: #008aff;"
                  "}"
                  "QSlider::handle:horizontal{"
                  "width: 12px;"
                  "margin-top: -5px;"
                  "margin-bottom: -4px;"
                  "border-radius: 6px;"
                  "background: qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 #565656,stop:0.8 #565656);"
                  "}");


    m_timer->setInterval(100);

    connect(m_timer, &QTimer::timeout, this, &VolumeSlider::onTimeout);
}

void VolumeSlider::setValue(const int value)
{
    if (m_pressed)
        return;

    blockSignals(true);
    QSlider::setValue(value);
    blockSignals(false);
}

void VolumeSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (!rect().contains(e->pos()))
            return;
        m_pressed = true;
        QSlider::setValue(1000.0 * e->x() / rect().width());
    }
}

void VolumeSlider::mouseMoveEvent(QMouseEvent *e)
{
    const int value = minimum() + (double((maximum()) - minimum()) * e->x() / rect().width());

    QSlider::setValue(std::max(std::min(1000, value), 0));
    emit valueChanged(std::max(std::min(1000, value), 0));
}

void VolumeSlider::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_pressed = false;
        emit requestPlaySoundEffect();
    }
    //        QTimer::singleShot(100, [this] {m_pressed = false;});
}

void VolumeSlider::wheelEvent(QWheelEvent *e)
{
    e->accept();

    m_timer->start();

    QSlider::setValue(value() + (e->delta() > 0 ? 10 : -10));
}

void VolumeSlider::onTimeout()
{
    m_timer->stop();
    emit requestPlaySoundEffect();
}
