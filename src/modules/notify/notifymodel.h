/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     listenerri <190771752ri@gmail.com>
 *
 * Maintainer: listenerri <190771752ri@gmail.com>
 *
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

using Notification = com::deepin::dde::Notification;

class NotifyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum NotifyDataRole{
        NotifyIdRole = Qt::UserRole + 1,
        NotifyNameRole = Qt::UserRole + 2,
        NotifySummaryRole = Qt::UserRole + 3,
        NotifyBodyRole = Qt::UserRole + 4,
        NotifyIconRole = Qt::UserRole + 5,
        NotifyTimeRole = Qt::UserRole + 6,
        NotifyRemoveRole = Qt::UserRole + 7,
        NotifyXOffsetRole = Qt::UserRole + 8,
        NotifyHoverRole = Qt::UserRole + 9
    };

    NotifyModel(QObject *parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

public Q_SLOTS:
    void clearAllNotify();
    void removeNotify(const QModelIndex &index);
    void showClearAllAnim(int maxXOffset);
    void showRemoveAnim(const QModelIndex &removeIndex, int maxXOffset);
    void setHoverIndex(const QModelIndex &index);

Q_SIGNALS:
    void removeAnimFinished(const QModelIndex &index);
    void clearAllAnimFinished();
    void notifyClearStateChanged(bool isClear);

protected:
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void onNotifyGetAllFinished(QDBusPendingCallWatcher *w);
    void addNotify(const QString &s);

private:
    Notification *m_dbus;

    QJsonArray m_dataJsonArray;
    QModelIndex m_removeIndex;
    QModelIndex m_hoverIndex;

    int m_currentXOffset;
    int m_maxXOffset;
    int m_animTimerID;
    bool m_isClearAll;
};

#endif // NOTIFYMODEL_H
