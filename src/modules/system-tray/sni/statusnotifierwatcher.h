/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     listenerri <listenerri@gmail.com>
 *
 * Maintainer: listenerri <listenerri@gmail.com>
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

#ifndef STATUSNOTIFIERWATCHER_H
#define STATUSNOTIFIERWATCHER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.kde.StatusNotifierWatcher
 */
class StatusNotifierWatcherInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.kde.StatusNotifierWatcher"; }

public:
    StatusNotifierWatcherInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~StatusNotifierWatcherInterface();

    Q_PROPERTY(bool IsStatusNotifierHostRegistered READ isStatusNotifierHostRegistered)
    inline bool isStatusNotifierHostRegistered() const
    { return qvariant_cast< bool >(property("IsStatusNotifierHostRegistered")); }

    Q_PROPERTY(int ProtocolVersion READ protocolVersion)
    inline int protocolVersion() const
    { return qvariant_cast< int >(property("ProtocolVersion")); }

    Q_PROPERTY(QStringList RegisteredStatusNotifierItems READ registeredStatusNotifierItems)
    inline QStringList registeredStatusNotifierItems() const
    { return qvariant_cast< QStringList >(property("RegisteredStatusNotifierItems")); }

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> RegisterStatusNotifierHost(const QString &service)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(service);
        return asyncCallWithArgumentList(QStringLiteral("RegisterStatusNotifierHost"), argumentList);
    }

    inline QDBusPendingReply<> RegisterStatusNotifierItem(const QString &service)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(service);
        return asyncCallWithArgumentList(QStringLiteral("RegisterStatusNotifierItem"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void StatusNotifierHostRegistered();
    void StatusNotifierHostUnregistered();
    void StatusNotifierItemRegistered(const QString &in0);
    void StatusNotifierItemUnregistered(const QString &in0);
};

namespace org {
  namespace kde {
    typedef ::StatusNotifierWatcherInterface StatusNotifierWatcher;
  }
}
#endif
