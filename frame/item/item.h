#ifndef ITEM_H
#define ITEM_H

#include "utils/itempopupwindow.h"
#include <QWidget>
#include <memory>

class Item : public QWidget
{
    Q_OBJECT
public:
    explicit Item(QWidget *parent = 0);
    enum ItemType {
        Indicator,
        Plugin,
        DateTime,
        Stretch
    };

    inline virtual ItemType itemType() const {Q_UNREACHABLE(); return Plugin;}
    virtual QWidget *popupTips();
    virtual const QPoint popupMarkPoint();
    virtual void showTips();
    virtual void showPopupWindow(QWidget * const content);
    virtual void hideTips();
    virtual PluginsItemInterface *itemInter();

protected:
    static std::unique_ptr<ItemPopupWindow> PopupWindow;
};

#endif // ITEM_H
