#include "stretchitem.h"

StretchItem::StretchItem(QWidget *parent) : Item(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Item::ItemType StretchItem::itemType() const
{
    return Stretch;
}

void StretchItem::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}
