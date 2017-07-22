#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>

namespace Plugin {
namespace DateTime {
DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent) {

    setStyleSheet("QLabel {"
                  "font: 14px;"
                  "color: rgb(67, 67, 62);"
                  "font-weight: 500;"
                  "background: transparent;"
                  "}"
                  "QLabel:hover {"
                  "color: white;"
                  "background: #1E90FF;"
                  "}");

    m_dateTime = new QDateTime;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();

    setContentsMargins(3, 0, 3, 0);
}

DateTimeWidget::~DateTimeWidget() {
    delete m_dateTime;
}

void DateTimeWidget::updateTime() {
    setText(m_dateTime->currentDateTime().toString(m_24HourFormat ? "hh:mm" : "hh:mm A"));
}

void DateTimeWidget::set24HourFormat(bool is24HourFormat)
{
    if (m_24HourFormat == is24HourFormat)
        return;

    m_24HourFormat = is24HourFormat;

    updateTime();
}
}
}
