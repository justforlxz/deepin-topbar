#include "networkdelegate.h"

#include "networklistmodel.h"

#include <QPainter>
#include <DHiDPIHelper>
#include <QApplication>
#include <QImageReader>

DWIDGET_USE_NAMESPACE

using namespace dtb;
using namespace dtb::network;

NetworkDelegate::NetworkDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{

}

void NetworkDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QString name { index.data(NetworkListModel::NameRole).toString() };
    const QString icon { index.data(NetworkListModel::IconRole).toString() };
    const bool isSecurity { index.data(NetworkListModel::SecurityRole).toBool() };

    if (index.data(NetworkListModel::HoverRole).toBool()) {
        painter->fillRect(option.rect, QColor(0, 0, 0, 0.1 * 255));
    }

    const QPixmap pixmap = DHiDPIHelper::loadNxPixmap(icon);
    QRect pixRect(option.rect.topLeft(), pixmap.size());
    painter->drawPixmap(pixRect, pixmap);

    QRect textRect(pixRect.topRight(), QSize(option.fontMetrics.width(name) + 10, option.fontMetrics.height()));
    painter->setPen(Qt::white);
    painter->drawText(textRect, name);

    if (isSecurity) {
        QPixmap securityPixmap;
        QImageReader reader;
        qreal sourceDevicePixelRatio = 1.0;
        qreal devicePixelRatio = qApp->devicePixelRatio();
        reader.setFileName(":/wireless/resources/wireless/security.svg");
        if (reader.canRead()) {
            reader.setScaledSize(QSize(48, 48) * (devicePixelRatio / sourceDevicePixelRatio));
            securityPixmap = QPixmap::fromImage(reader.read());
            securityPixmap.setDevicePixelRatio(devicePixelRatio);
        }
        QRect securityRect(QPoint(option.rect.width() - securityPixmap.width() / devicePixelRatio - 10, option.rect.y()), securityPixmap.size() / devicePixelRatio);
        painter->drawPixmap(securityRect, securityPixmap);
    }
}

QSize NetworkDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return index.data(NetworkListModel::SizeRole).toSize();
}
