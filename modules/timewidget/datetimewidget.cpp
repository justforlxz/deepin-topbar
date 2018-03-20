#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QHBoxLayout>

namespace Plugin {
namespace DateTime {
DateTimeWidget::DateTimeWidget(QWidget *parent)
    : ContentModule(parent)
{
    setStyleSheet("QLabel {color: #d3d3d3;}");

    m_dateTime = new QDateTime;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();

    m_timeLbl = new QLabel;
    m_timeLbl->setAlignment(Qt::AlignVCenter);

    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);

    layout->addWidget(m_timeLbl, 0, Qt::AlignCenter);

    setLayout(layout);

    m_format = "yyyy-MM-dd hh:mm";
}

DateTimeWidget::~DateTimeWidget() {
    delete m_dateTime;
}

void DateTimeWidget::updateTime() {
    m_timeLbl->setText(m_dateTime->currentDateTime().toString(m_format + (m_24HourFormat ? "" : " A")));
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
