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

#include "notifymodel.h"

#include <QJsonObject>
#include <QDate>

using namespace dtb;
using namespace dtb::notify;

NotifyModel::NotifyModel(QObject *parent) : QAbstractListModel(parent)
{
    m_notifyDBus = new Notification("com.deepin.dde.Notification",
                                     "/com/deepin/dde/Notification",
                                     QDBusConnection::sessionBus(), this);

    m_notifyDBus->setSync(false);

    connect(m_notifyDBus, &Notification::RecordAdded, this, &NotifyModel::onNotifyAdded);

    QDBusPendingCallWatcher *notifyWatcher = new QDBusPendingCallWatcher(m_notifyDBus->GetAllRecords(), this);
    connect(notifyWatcher, &QDBusPendingCallWatcher::finished, this, &NotifyModel::onNotifyGetAllFinished);
}

int NotifyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_itemList.size();
}

QVariant NotifyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (rowCount(QModelIndex()) <= index.row())
        return QVariant();

    const NotifyItem *item = indexof(index.row());

    if (!item)
        return QVariant();

    switch (role) {
    case Qt::SizeHintRole: return QSize(360, 80);
    case ItemNameRole:
        return item->name;
    case ItemBodyRole:
        return item->body;
    case ItemIconRole:
        return item->icon;
    case ItemIdRole:
        return item->id;
    case ItemTimeRole:
        return item->time;
    case ItemHoveredRole:
        return m_currentIndex == index;
    default:
        break;
    }

    return QVariant();
}

const NotifyItem* NotifyModel::indexof(const int index) const
{
    const int size = m_itemList.size() - 1;

    //Reverse
    return size <= 0 ? nullptr : m_itemList[size - index];
}

void NotifyModel::setCurrentHovered(const QModelIndex &index)
{
    m_currentIndex = index;

    emit dataChanged(m_currentIndex, m_currentIndex);
}

void NotifyModel::onNotifyGetAllFinished(QDBusPendingCallWatcher *w)
{
    QDBusPendingReply<QString> reply = *w;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply.value().toLocal8Bit().data());

    m_dataJsonArray = jsonDocument.array();

    m_checkIndex = m_dataJsonArray.size();

    if (m_dataJsonArray.size()) {

        for (int i(0); i != m_dataJsonArray.size(); ++i) {

            NotifyItem * item = new NotifyItem;
            m_itemList << item;

            const QJsonObject &obj = m_dataJsonArray[i].toObject();

            item->name = obj["summary"].toString();
            item->body = obj["body"].toString();
            item->icon = obj["icon"].toString();
            item->id   = obj["id"].toString();
            item->time = checkDate(obj["id"].toString());
        }

        emit layoutChanged();
    }

    w->deleteLater();
}

void NotifyModel::onNotifyAdded(const QString &value)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(value.toLocal8Bit().data());

    NotifyItem * item = new NotifyItem;
    m_itemList << item;

    const QJsonObject &obj = jsonDocument.object();

    item->name = obj["summary"].toString();
    item->body = obj["body"].toString();
    item->icon = obj["icon"].toString();
    item->id   = obj["id"].toString();
    item->time = checkDate(obj["id"].toString());

    // update

}

QString NotifyModel::checkDate(const QString &value)
{
    const QDateTime date = QDateTime::fromMSecsSinceEpoch(value.toLongLong());

    QString result;

    if (QDateTime::currentMSecsSinceEpoch() > value.toLongLong()) {

        const QString hour = date.toString("hh:mm");

        const uint year = date.date().year();
        uint now = QDateTime::currentDateTime().date().year();

        if (now > year)
            result = date.toString("yyyy/MM/dd hh:mm");
        else {
            const uint notify_day = date.date().day();
            now = QDateTime::currentDateTime().date().day();

            const uint month = date.date().month();
            const uint now_month = QDateTime::currentDateTime().date().month();

            if (now_month == month) {

                //contrast day
                const uint time = now - notify_day;

                switch (time) {
                case 0:
                    result = hour;
                    break;
                case 1:
                    result = tr("Yesterday") + " " + hour;
                    break;
                case 2:
                    result = tr("The day before yesterday") + " " + hour;
                    break;
                default:
                    if (time > 7) {
                        result = date.toString("MM/dd hh:mm");
                    } else {
                        result = tr("%n day(s) ago", "", time) + " " + hour;
                    }
                    break;
                }
            } else {
                result = date.toString("MM/dd hh:mm");
            }
        }
    } else {
        result = date.toString("yyyy/MM/dd hh:mm");
    }

    return result;
}
