#include "item.h"
#include <QDebug>

std::unique_ptr<ItemPopupWindow> Item::PopupWindow(nullptr);

Item::Item(QWidget *parent)
    : QWidget(parent)
{
    if (!PopupWindow.get())
    {
        ItemPopupWindow *arrowRectangle = new ItemPopupWindow(nullptr);
        arrowRectangle->setShadowBlurRadius(20);
        arrowRectangle->setRadius(6);
        arrowRectangle->setShadowDistance(0);
        arrowRectangle->setShadowYOffset(2);
        arrowRectangle->setShadowXOffset(0);
        arrowRectangle->setArrowWidth(18);
        arrowRectangle->setArrowHeight(10);
        PopupWindow.reset(arrowRectangle);
    }
}

QWidget *Item::popupTips()
{
    return nullptr;
}

const QPoint Item::popupMarkPoint()
{
    QPoint p;
    QWidget *w = this;
    do {
        p += w->pos();
        w = qobject_cast<QWidget *>(w->parent());
    } while (w);

    const QRect r = rect();
    const int offset = 5;
    p += QPoint(r.width() / 2, r.height() + offset);

    return p;
}

void Item::showTips()
{
    QWidget * const content = popupTips();
    if (!content)
        return;

    showPopupWindow(content);
}

void Item::showPopupWindow(QWidget * const content)
{
    ItemPopupWindow *popup = PopupWindow.get();
    QWidget *lastContent = popup->getContent();
    if (lastContent)
        lastContent->setVisible(false);

    popup->setArrowDirection(ItemPopupWindow::ArrowTop);
    popup->setItemInter(itemInter());
    popup->setContent(content);
    popup->setWidth(content->sizeHint().width());
    popup->setHeight(content->sizeHint().height());

    const QPoint p = popupMarkPoint();
    QMetaObject::invokeMethod(popup, "show", Qt::QueuedConnection, Q_ARG(QPoint, p));
}

void Item::hidePopup()
{
    PopupWindow->setVisible(false);
}

PluginsItemInterface *Item::itemInter()
{
    return nullptr;
}
