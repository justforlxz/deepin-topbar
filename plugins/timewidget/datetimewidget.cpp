#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QDebug>

DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent)
{
    popup = new DateTimePopup;
    QSettings *settings = new QSettings("deepin", "dde-dock-datetime", this);
    m_24HourFormat = settings->value("24HourFormat").toBool();

    popup->onDateFormatChanged(m_24HourFormat);

    m_dateTime = new QDateTime;
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &DateTimeWidget::updateTime);
    timer->start();

    connect(popup, &DateTimePopup::requestDateFormat, this, [=] (const bool state) {
        settings->setValue("24HourFormat", state ? 24 : 12);
        m_24HourFormat = state;
        updateTime();
    });
}

DateTimeWidget::~DateTimeWidget()
{
    delete m_dateTime;
}

QWidget *DateTimeWidget::popupWidget()
{
    return popup;
}

void DateTimeWidget::updateTime()
{
    setText(m_dateTime->currentDateTime().toString(m_24HourFormat ? "hh:mm" : "hh:mm A"));
}
