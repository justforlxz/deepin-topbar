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

#ifndef NOTIFYMODEL_H
#define NOTIFYMODEL_H

#include <QAbstractListModel>
#include <com_deepin_dde_notification.h>
#include <QDir>

using Notification = com::deepin::dde::Notification;

static const QStringList Directory = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
static const QString CacheFolder = Directory.first() + "/.cache/deepin/deepin-notifications/";

namespace dtb {
namespace notify {

struct NotifyItem {
    QString name;
    QString body;
    QString icon;
    QString id;
    QString time;
};

class NotifyModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit NotifyModel(QObject *parent = nullptr);

    enum NotifyRole {
        UnusedRole = Qt::UserRole,
        ItemHoveredRole,
        ItemNameRole,
        ItemBodyRole,
        ItemIconRole,
        ItemIdRole,
        ItemTimeRole
    };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    const NotifyItem *indexof(const int index) const;

public slots:
    void setCurrentHovered(const QModelIndex &index);

private slots:
    void onNotifyGetAllFinished(QDBusPendingCallWatcher *w);
    void onNotifyAdded(const QString &value);

private:
    QString checkDate(const QString &value);

private:
    Notification* m_notifyDBus;
    QJsonArray m_dataJsonArray;
    int m_checkIndex;
    QList<NotifyItem*> m_itemList;
    QModelIndex m_currentIndex;
};
}
}

#endif // NOTIFYMODEL_H
