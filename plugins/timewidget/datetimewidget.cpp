#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QSettings>
#include <QHBoxLayout>

DateTimeWidget::DateTimeWidget(QWidget *parent) : QWidget(parent)
{

    m_timeLbl = new QLabel;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_timeLbl, 0, Qt::AlignVCenter);

    setLayout(layout);

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
    m_timeLbl->setText(m_dateTime->currentDateTime().toString(m_24HourFormat ? "hh:mm" : "hh:mm A"));
}
