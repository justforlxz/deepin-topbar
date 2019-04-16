#ifndef ITEM_H
#define ITEM_H

#include "interfaces/pluginsiteminterface.h"
#include "widgets/itempopupwindow.h"
#include <QWidget>
#include <memory>

namespace dtb {
class Item : public QWidget
{
    Q_OBJECT
public:
    explicit Item(QWidget *parent = 0);

    virtual const QString name() const {return QString();}
    virtual PluginsItemInterface *itemInter();
    virtual QWidget* contextMenu() const;
    void hidePopupWindow();

protected:
    static std::unique_ptr<ItemPopupWindow> PopupWindow;
};
}

#endif // ITEM_H
