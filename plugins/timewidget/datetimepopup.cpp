#include "datetimepopup.h"
#include <QVBoxLayout>
#include <QProcess>
#include <QPushButton>

using namespace topbar::widgets;

namespace Plugin {
namespace DateTime {
DateTimePopup::DateTimePopup(QWidget *parent) : QWidget(parent) {
    setWindowFlags(Qt::FramelessWindowHint);

    m_dateBtn = new SwitchItem;
    m_dateBtn->setText(tr("Is 24 datetime"));

    m_posBtn = new SwitchItem;
    m_posBtn->setText(tr("Change Position"));

    m_formatBtn = new SwitchItem;
    m_formatBtn->setText(tr("Is Full date"));

    QPushButton *btn = new QPushButton(tr("DateTime Settings"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);

    mainLayout->addWidget(m_posBtn);
    mainLayout->addWidget(m_dateBtn);
    mainLayout->addWidget(m_formatBtn);
    mainLayout->addWidget(btn);

    setLayout(mainLayout);
    connect(m_dateBtn, &SwitchItem::clicked, this, &DateTimePopup::requestDateFormat);
    connect(btn, &QPushButton::clicked, this, [=]{
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");
        emit requestHide();
    });

    connect(m_posBtn, &SwitchItem::clicked, this, &DateTimePopup::requestIsCenterChanged);

    connect(m_formatBtn, &SwitchItem::clicked, this, [=] (const bool state) {
            if (state)
                m_format = "yyyy-MM-dd ddd hh:mm";
            else
                m_format = "hh:mm";

            emit requestFormatChanged(m_format);
    });
}

void DateTimePopup::onDateFormatChanged(const bool state) {
    m_dateBtn->setCheck(state);
}

QString DateTimePopup::format() const
{
    return m_format;
}

void DateTimePopup::setFormat(const QString &format)
{
    if (m_format == format)
        return;

    m_format = format;

    m_formatBtn->setCheck(format == "yyyy-MM-dd ddd hh:mm");
}

bool DateTimePopup::is24Format() const
{
    return m_dateBtn->checked();
}

void DateTimePopup::setIs24Format(bool is24Format)
{
    if (m_is24Format == is24Format)
        return;

    m_is24Format = is24Format;

    m_dateBtn->setCheck(is24Format);
}

bool DateTimePopup::isCenter() const
{
    return m_posBtn->checked();
}

void DateTimePopup::setIsCenter(bool isCenter)
{
    if (m_isCenter == isCenter)
        return;

    m_isCenter = isCenter;

    m_posBtn->setCheck(isCenter);
}
}
}
