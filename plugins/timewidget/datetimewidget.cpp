#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QDebug>

DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent)
{
    QTimer *timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();
}

void DateTimeWidget::updateTime()
{
    QDateTime t;
    setText(t.currentDateTime().toString("yyyy年MM月dd日 hh:mm:ss"));
}
