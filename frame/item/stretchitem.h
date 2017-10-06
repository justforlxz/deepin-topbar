#ifndef STRETCHITEM_H
#define STRETCHITEM_H

#include "item.h"

namespace dtb {
class StretchItem : public Item
{
    Q_OBJECT
public:
    explicit StretchItem(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *e);
};
}

#endif // STRETCHITEM_H
