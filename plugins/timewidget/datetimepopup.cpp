#include "datetimepopup.h"
#include <QVBoxLayout>

DateTimePopup::DateTimePopup(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    SwitchItem *_12DateBtn = new SwitchItem;
    _12DateBtn->setText("12小时制");
    _12DateBtn->setValue("12");
    m_buttonGrp.append(_12DateBtn);

    SwitchItem *_24DateBtn = new SwitchItem;
    _24DateBtn->setText("24小时制");
    _24DateBtn->setValue("24");
    m_buttonGrp.append(_24DateBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(_12DateBtn);
    mainLayout->addWidget(_24DateBtn);

    setLayout(mainLayout);
    connect(_12DateBtn, &SwitchItem::clicked, this, &DateTimePopup::onDateFormatChanged);
    connect(_24DateBtn, &SwitchItem::clicked, this, &DateTimePopup::onDateFormatChanged);
}

void DateTimePopup::onDateFormatChanged(const bool state)
{
    Q_UNUSED(state);

    SwitchItem *button = qobject_cast<SwitchItem*>(sender());
    emit requestDateFormat(button->value().toInt() == 24);

    for (SwitchItem *btn : m_buttonGrp) {
        if (btn != button)
            btn->setCheck(false);
    }
}

void DateTimePopup::onSetDefaultDateFormat(int format)
{
    for (SwitchItem *btn : m_buttonGrp) {
        btn->setCheck(btn->value().toInt() == format);
    }
}
