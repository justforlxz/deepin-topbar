#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>

namespace Plugin {
namespace DateTime {
DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent) {

    m_dateTime = new QDateTime;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();

    setAlignment(Qt::AlignVCenter);

    setFixedHeight(26);

    setContentsMargins(3, 0, 3, 0);

    m_format = "yyyy-MM-dd hh:mm";
}

DateTimeWidget::~DateTimeWidget() {
    delete m_dateTime;
}

void DateTimeWidget::updateTime() {
    setText(m_dateTime->currentDateTime().toString(m_format + (m_24HourFormat ? "" : " A")));
}

void DateTimeWidget::set24HourFormat(bool is24HourFormat)
{
    if (m_24HourFormat == is24HourFormat)
        return;

    m_24HourFormat = is24HourFormat;

    updateTime();
}

void DateTimeWidget::setFormat(const QString &value)
{
    if (!value.isEmpty())
        m_format = value;

    updateTime();
}
}
}
