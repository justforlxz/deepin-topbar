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

#ifndef NOTIFYDELEGATE_H
#define NOTIFYDELEGATE_H

#include <QStyledItemDelegate>
#include <QStandardPaths>

static const QSize IconSize = QSize(48, 48);
static const QStringList Directory = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
static const QString CacheFolder = Directory.first() + "/.cache/deepin/deepin-notifications/";

class NotifyDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    NotifyDelegate(QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void removeBtnClicked() const;

public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QPixmap notifyPixmap(const QString &name, QPaintDevice *device) const;
    QString notifyTime(const QString &t) const;
    const QPair<QString, bool> holdTextInRect(const QFontMetrics &fm, const QString &text, const QRect &rect) const;

private:
    mutable QList<QPair<QPair<QString, QRect>, QPair<QString, bool>>> m_textCache;
};

#endif // NOTIFYDELEGATE_H
