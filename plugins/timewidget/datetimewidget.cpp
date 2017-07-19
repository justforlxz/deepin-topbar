#include "datetimewidget.h"
#include <QTimer>
#include <QDateTime>
#include <QSettings>

namespace Plugin {
namespace DateTime {
DateTimeWidget::DateTimeWidget(QWidget *parent) : QLabel(parent) {

    setStyleSheet("QLabel {"
                  "font: 14px;"
                  "color: black;"
                  "background: transparent;"
                  "}"
                  "QLabel:hover {"
                  "color: white;"
                  "background: #1E90FF;"
                  "}");

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
        settings->setValue("24HourFormat", state);
        m_24HourFormat = state;
        updateTime();
    });

    setContentsMargins(3, 0, 3, 0);
}

DateTimeWidget::~DateTimeWidget() {
    delete m_dateTime;
}

DateTimePopup *DateTimeWidget::popupWidget() {
    return popup;
}

void DateTimeWidget::updateTime() {
    setText(m_dateTime->currentDateTime().toString(m_24HourFormat ? "hh:mm" : "hh:mm A"));
}
}
}
