#include "item.h"
#include <QDebug>

std::unique_ptr<ItemPopupWindow> Item::PopupWindow(nullptr);

Item::Item(QWidget *parent)
    : QWidget(parent)
{
    if (!PopupWindow.get())
    {
        ItemPopupWindow *arrowRectangle = new ItemPopupWindow(nullptr);
        PopupWindow.reset(arrowRectangle);
    }
}

QWidget *Item::popupTips()
{
    return nullptr;
}

const QRect Item::popupMarkGeometry()
{
    return QRect();
}

PluginsItemInterface *Item::itemInter()
{
    return nullptr;
}
