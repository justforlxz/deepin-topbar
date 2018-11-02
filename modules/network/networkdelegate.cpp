#include "networkdelegate.h"

#include "networklistmodel.h"

#include <QPainter>

using namespace dtb;
using namespace dtb::network;

NetworkDelegate::NetworkDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void NetworkDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QString name { index.data(NetworkListModel::NameRole).toString() };

    painter->setPen(Qt::white);
    painter->drawText(option.rect, name);
}

QSize NetworkDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return index.data(NetworkListModel::SizeRole).toSize();
}
