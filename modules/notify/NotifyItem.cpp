#include "NotifyItem.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

NotifyItem::NotifyItem(const QJsonObject &json, QWidget *parent) : QWidget(parent)
{
    // main layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    setLayout(layout);

    //title layout
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setMargin(0);
    titleLayout->setSpacing(0);


    // smail icon
    QLabel *icon = new QLabel;
    titleLayout->addWidget(icon);
    titleLayout->addSpacing(2);

    QLabel *label = new QLabel;
    label->setText(json["Title"].toString());
    titleLayout->addWidget(label);
    titleLayout->addStretch();
    // titlelayout add close button

    //body layout
    QHBoxLayout *bodylayout = new QHBoxLayout;
    bodylayout->setMargin(0);
    bodylayout->setSpacing(0);

    QLabel *body = new QLabel;
    bodylayout->addWidget(body);

    //body text need be process into a line

    // add show all info button
    QPushButton *button = new QPushButton;

}
