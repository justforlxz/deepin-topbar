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

#include "dactionbutton.h"

#include <QEvent>
#include <QPainter>

using namespace dtb;
using namespace dtb::widgets;

DActionButton::DActionButton(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout)
    , m_isEnter(false)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedHeight(30);

    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    setLayout(m_layout);

    installEventFilter(this);
}

void DActionButton::setContent(QWidget *widget)
{
    m_layout->addWidget(widget);
}

bool DActionButton::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        if (event->type() == QEvent::Enter) {
            m_isEnter = true;
            update();
        }

        if (event->type() == QEvent::Leave) {
            m_isEnter = false;
            update();
        }

        if (event->type() == QEvent::Paint) {
            QPainter painter(this);
            painter.fillRect(rect(), m_isEnter ? QColor("#2CA7F8") : QColor(0, 0, 0, 0));
        }
    }

    return QWidget::eventFilter(watched, event);
}
