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
    m_dateBtn->setText(tr("Format Change"));

    m_posBtn = new SwitchItem;
    m_posBtn->setText(tr("Change Position"));

    QPushButton *btn = new QPushButton(tr("DateTime Settings"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);

    mainLayout->addWidget(m_posBtn);
    mainLayout->addWidget(m_dateBtn);
    mainLayout->addWidget(btn);

    setLayout(mainLayout);
    connect(m_dateBtn, &SwitchItem::clicked, this, &DateTimePopup::requestDateFormat);
    connect(btn, &QPushButton::clicked, this, [=]{
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");
        emit requestHide();
    });

    connect(m_posBtn, &SwitchItem::clicked, this, &DateTimePopup::requestIsCenterChanged);
}

void DateTimePopup::onDateFormatChanged(const bool state) {
    m_dateBtn->setCheck(state);
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
