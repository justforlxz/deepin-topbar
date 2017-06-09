#include "timewidget.h"
#include <QTimer>
#include <QDateTime>

TimeWidget::TimeWidget(QWidget *parent) : QLabel(parent)
{
    QTimer *timer = new QTimer(this);
    timer->start();

    connect(timer, &QTimer::timeout, this, &TimeWidget::onTimeout);
}

void TimeWidget::onTimeout()
{
    QDateTime t;
    setText(t.currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss"));
}
