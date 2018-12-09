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

#include "notifyview.h"
#include "notifymodel.h"

NotifyView::NotifyView(QWidget *parent) : QListView(parent)
{
    setFrameStyle(QFrame::NoFrame);
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setSpacing(0);
    setContentsMargins(0, 0, 0, 0);
    setUpdatesEnabled(true);
    setStyleSheet("background-color: rgba(255, 255, 255, 7.65);");

    connect(this, &NotifyView::currentHoverChanged, this, &NotifyView::onCurrentHoverChanged);
    connect(this, &NotifyView::entered, this, &NotifyView::onItemEntered);
}

const QModelIndex &NotifyView::currentHoverIndex() const
{
    return m_indexCurrent;
}

void NotifyView::enterEvent(QEvent *event)
{
    if (m_indexCurrent.isValid()) {
        openPersistentEditor(m_indexCurrent);
    }

    QWidget::enterEvent(event);
}

void NotifyView::leaveEvent(QEvent *event)
{
    if (m_indexCurrent.isValid()) {
        closePersistentEditor(m_indexCurrent);
        static_cast<NotifyModel *>(model())->setHoverIndex(QModelIndex());
    }
    QWidget::leaveEvent(event);
}

void NotifyView::onCurrentHoverChanged(const QModelIndex &previous, const QModelIndex &current)
{
    if (previous.isValid()) {
        closePersistentEditor(previous);
    }
    openPersistentEditor(current);
}

void NotifyView::onItemEntered(const QModelIndex &index)
{
    m_indexCurrent = index;
    static_cast<NotifyModel *>(model())->setHoverIndex(m_indexCurrent);
    if (m_indexPrevious != m_indexCurrent) {
        Q_EMIT currentHoverChanged(m_indexPrevious, m_indexCurrent);
        m_indexPrevious = m_indexCurrent;
    }
}
