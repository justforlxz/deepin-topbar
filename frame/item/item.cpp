#include "item.h"
#include <QDebug>

using namespace dtb;

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

const QRect Item::popupMarkGeometry() const
{
    return QRect();
}

PluginsItemInterface *Item::itemInter()
{
    return nullptr;
}

QMenu *Item::contextMenu() const
{
    return new QMenu();
}
