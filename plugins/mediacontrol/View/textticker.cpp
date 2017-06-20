#include "textticker.h"
#include <QTimer>
#include <QHBoxLayout>
#include <QPainter>
#include <QPen>

TextTicker::TextTicker(QWidget *parent) : QLabel(parent)
{
    m_curIndex = 0;

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &TextTicker::updateIndex);
}

void TextTicker::setText(const QString &source)
{
    m_showText = source;

    // I think move speed is 2 very good.
    m_moveSpeed = 2;

    m_isFirstPlay = true;

    m_timer->stop();
    m_curIndex = 0;
    m_timer->start(100);
}

void TextTicker::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    QPainter painter(this);

    // if the character is completely moved out of the interface, from the right

    QPen pen(painter.pen());
    pen.setWidth(14);
    painter.setPen(pen);

    painter.drawText(width() - m_moveSpeed * m_curIndex, 18.5, m_showText);

    if (m_curIndex * m_moveSpeed > fontMetrics().width(m_showText) + width())
        m_curIndex = 0;
}

void TextTicker::updateIndex()
{
    update();
    m_curIndex++;
}
