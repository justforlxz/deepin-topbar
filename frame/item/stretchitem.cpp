#include "stretchitem.h"
#include <QLabel>

StretchItem::StretchItem(QWidget *parent) : Item(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QLabel *label = new QLabel(this);
    label->setFixedWidth(100);
    label->setStyleSheet("background: red;");
    setStyleSheet("background: blue;");
}

Item::ItemType StretchItem::itemType() const
{
    return Stretch;
}

void StretchItem::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}
