#include "item.h"
#include <QDebug>

using namespace dtb;

std::unique_ptr<ItemPopupWindow> Item::PopupWindow(nullptr);

Item::Item(QWidget *parent)
    : QWidget(parent)
{
    if (!PopupWindow.get()) {
        ItemPopupWindow *arrowRectangle = new ItemPopupWindow(nullptr);
        PopupWindow.reset(arrowRectangle);
    }
}

PluginsItemInterface *Item::itemInter()
{
    return nullptr;
}

QWidget *Item::contextMenu() const
{
    return nullptr;
}

void Item::hidePopupWindow()
{
    if (PopupWindow.get()) {
        PopupWindow->hide();
    }
}
