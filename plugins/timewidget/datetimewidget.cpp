#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>

DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent)
{
    m_dateTime = new QDateTime;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();
}

DateTimeWidget::~DateTimeWidget()
{
    delete m_dateTime;
}

void DateTimeWidget::updateTime()
{
    setText(m_dateTime->currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss"));
}
