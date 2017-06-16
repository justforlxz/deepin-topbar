#ifndef ITEM_H
#define ITEM_H

#include <QWidget>

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
};

#endif // ITEM_H
