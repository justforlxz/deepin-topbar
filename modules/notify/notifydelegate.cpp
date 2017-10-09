/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "notifydelegate.h"
#include "notifymodel.h"

#include <QPainter>
#include <QApplication>
#include <QImageReader>

using namespace dtb;
using namespace dtb::notify;

static QSize iconSize(48, 48);

const QPixmap getPixmap(const QString &path)
{
    const qreal devicePixelRatio = qApp->devicePixelRatio();

    QPixmap pixmap;

    const QIcon &icon = QIcon::fromTheme(path, QIcon::fromTheme("application-x-desktop"));

    if (!icon.isNull()) {
        pixmap = icon.pixmap(iconSize * devicePixelRatio)
                .scaled(iconSize * devicePixelRatio,
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation);

        pixmap.setDevicePixelRatio(devicePixelRatio);
    }

    return pixmap;
}

NotifyDelegate::NotifyDelegate(QObject *parent) : QAbstractItemDelegate(parent)
{

}

void NotifyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QString &appName = index.data(NotifyModel::ItemNameRole).toString();
    const QString &appId   = index.data(NotifyModel::ItemIdRole).toString();
    QPixmap appIcon;

    const QString &path = index.data(NotifyModel::ItemIconRole).toString();
    if (path.isEmpty())
        appIcon = getPixmap(CacheFolder + appId + ".png");
    else
        appIcon = getPixmap(path);

    const QString &appBody = index.data(NotifyModel::ItemBodyRole).toString();
    const QString &appTime = index.data(NotifyModel::ItemTimeRole).toString();
    const bool isHover = index.data(NotifyModel::ItemHoveredRole).toBool();

    const int x = 15;
    const int y = option.rect.top() + (option.rect.height() - 48) / 2;

    // draw app icon
    painter->drawPixmap(x, y, appIcon);

    // Designer's needs: the title and content are vertically centered as a whole

    if (isHover) {
        // draw background
        QPainterPath path;
        path.addRoundedRect(option.rect, 4, 4);

        painter->fillPath(path, QColor(254, 254, 254, 0.13 * 255));

        // draw close button

    } else {
        // draw app time
        painter->drawText(option.rect.marginsRemoved(QMargins(50, 0, 0, 0)),
                          Qt::AlignLeft | Qt::AlignVCenter, appTime);
    }
}

QSize NotifyDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);

    return index.data(Qt::SizeHintRole).toSize();
}
