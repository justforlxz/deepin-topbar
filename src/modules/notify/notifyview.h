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

#ifndef NOTIFYVIEW_H
#define NOTIFYVIEW_H

#include <QListView>

class NotifyView : public QListView
{
    Q_OBJECT

public:
    NotifyView(QWidget *parent = Q_NULLPTR);

    const QModelIndex &currentHoverIndex() const;

Q_SIGNALS:
    void currentHoverChanged(const QModelIndex &previous, const QModelIndex &current);

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;

private Q_SLOTS:
    void onCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current);
    void onItemEntered(const QModelIndex &index);

private:
    QModelIndex m_indexPrevious;
    QModelIndex m_indexCurrent;
};

#endif // NOTIFYVIEW_H
