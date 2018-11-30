/*
 * Copyright 2011 Canonical Ltd.
 * Copyright 2014 Dmitry Shachnev <mitya57@ubuntu.com>
 *
 * Maintainer: listenerri <listenerri@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Based on sni-qt code by Aurelien Gateau <aurelien.gateau@canonical.com>.
 */

#ifndef DBUSSTRUCTURES_H
#define DBUSSTRUCTURES_H

#include <QtCore/qbytearray.h>
#include <QtCore/qstring.h>
#include <QtCore/qlist.h>
#include <QtGui/qicon.h>
#include <QtGui/qpixmap.h>
#include <QtDBus/qdbusargument.h>

struct DBusImage
{
    int width;
    int height;
    QByteArray pixels;
};
Q_DECLARE_METATYPE(DBusImage)

typedef QList<DBusImage> DBusImageList;
Q_DECLARE_METATYPE(DBusImageList)

struct DBusToolTip
{
    QString iconName;
    DBusImageList iconPixmap;
    QString title;
    QString description;
};
Q_DECLARE_METATYPE(DBusToolTip)

QDBusArgument &operator<<(QDBusArgument&, const DBusImage&);
const QDBusArgument &operator>>(const QDBusArgument&, DBusImage&);

QDBusArgument &operator<<(QDBusArgument&, const DBusToolTip&);
const QDBusArgument &operator>>(const QDBusArgument&, DBusToolTip&);

void registerMetaTypes();

#endif /* DBUSSTRUCTURES_H */
