/*
 * Copyright (C) 2016 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#include "widgets/settingsgroup.h"
#include "widgets/settingsitem.h"

#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>

namespace dtb {
namespace widgets {


SettingsGroup::SettingsGroup(QFrame *parent) :
    TranslucentFrame(parent),
    m_layout(new QVBoxLayout),
    m_updateHeightTimer(new QTimer(this)),
    m_updateHeadTailTimer(new QTimer(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(1);

    m_updateHeightTimer->setSingleShot(true);
    m_updateHeightTimer->setInterval(10);

    m_updateHeadTailTimer->setSingleShot(true);
    m_updateHeadTailTimer->setInterval(10);

    connect(m_updateHeightTimer, &QTimer::timeout, this, &SettingsGroup::updateHeight, Qt::QueuedConnection);
    connect(m_updateHeadTailTimer, &QTimer::timeout, this, &SettingsGroup::updateHeadTail, Qt::QueuedConnection);

    setLayout(m_layout);
}

SettingsGroup::SettingsGroup(const QString &title, QFrame *parent)
    : SettingsGroup(parent)
{
    setAccessibleName(title);
}

SettingsGroup::~SettingsGroup()
{
}

void SettingsGroup::insertItem(const int index, SettingsItem *item)
{
    m_layout->insertWidget(index, item);
    item->installEventFilter(this);

    m_updateHeadTailTimer->start();
    m_updateHeightTimer->start();
}

void SettingsGroup::appendItem(SettingsItem *item)
{
    insertItem(m_layout->count(), item);
}

void SettingsGroup::removeItem(SettingsItem *item)
{
    m_layout->removeWidget(item);
    item->removeEventFilter(this);

    m_updateHeadTailTimer->start();
    m_updateHeightTimer->start();
}

void SettingsGroup::moveItem(SettingsItem *item, const int index)
{
    const int oldIndex = m_layout->indexOf(item);
    if (oldIndex == index)
        return;

    m_layout->removeWidget(item);
    m_layout->insertWidget(index, item);

    const int max = m_layout->count() - 1;
    if (index == 0 || index == max ||
        oldIndex == 0 || oldIndex == max)
        m_updateHeadTailTimer->start();
}

void SettingsGroup::setSpacing(const int spaceing)
{
    m_layout->setSpacing(spaceing);

    m_updateHeightTimer->start();
}

int SettingsGroup::itemCount() const
{
    return m_layout->count();
}

void SettingsGroup::clear()
{
    const int index = 0;
    const int count = m_layout->count();

    for (int i(index); i != count; ++i)
    {
        QLayoutItem *item = m_layout->takeAt(index);
        QWidget *w = item->widget();
        w->removeEventFilter(this);
        w->setParent(nullptr);
        delete item;
    }

    m_updateHeadTailTimer->start();
    m_updateHeightTimer->start();
}

SettingsItem *SettingsGroup::getItem(int index)
{
    if(index < 0)
        return NULL;

    if(index < itemCount())
    {
        return qobject_cast<SettingsItem *>(m_layout->itemAt(index)->widget());
    }

    return NULL;
}

bool SettingsGroup::eventFilter(QObject *, QEvent *event)
{
//    if (event->type() == QEvent::Resize || event->type() == QEvent::Show || event->type() == QEvent::Hide)
//        m_updateHeightTimer->start();

    switch (event->type())
    {
    case QEvent::Show:
    case QEvent::Hide:          m_updateHeadTailTimer->start();     // not break

    case QEvent::Resize:        m_updateHeightTimer->start();       break;
    default:;
    }

    return false;
}

void SettingsGroup::updateHeadTail()
{
    SettingsItem *head = nullptr;
    SettingsItem *tail = nullptr;

    const int count = m_layout->count();
    for (int i(0); i != count; ++i)
    {
        SettingsItem *item = qobject_cast<SettingsItem *>(m_layout->itemAt(i)->widget());
        Q_ASSERT(item);

        if (!item->isVisible())
            continue;

        item->setIsHead(false);
        item->setIsTail(false);

        if (!head)
            head = item;
        tail = item;
    }

    if (head)
        head->setIsHead();
    if (tail)
        tail->setIsTail();
}

void SettingsGroup::updateHeight()
{
    Q_ASSERT(sender() == m_updateHeightTimer);

    setFixedHeight(m_layout->sizeHint().height());
}

}
}
