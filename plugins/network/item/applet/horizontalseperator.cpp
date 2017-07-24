#include "horizontalseperator.h"

#include <QPainter>

HorizontalSeperator::HorizontalSeperator(QWidget *parent)
    : QWidget(parent),
      m_color(255, 255, 255, 255 * 0.1)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void HorizontalSeperator::setColor(const QColor color)
{
    m_color = color;
}

void HorizontalSeperator::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);

    QPainter painter(this);
    painter.fillRect(rect(), m_color);
}
