#include "datetimepopup.h"
#include <QVBoxLayout>

DateTimePopup::DateTimePopup(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    _DateBtn = new SwitchItem;
    _DateBtn->setText("时制切换");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);

    mainLayout->addWidget(_DateBtn);

    setLayout(mainLayout);
    connect(_DateBtn, &SwitchItem::clicked, this, &DateTimePopup::requestDateFormat);
}

void DateTimePopup::onDateFormatChanged(const bool state)
{
    _DateBtn->setCheck(state);
}
