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

#include "dwidgetaction.h"
#include <QEvent>
#include <QPainter>

using namespace dtb;
using namespace dtb::widgets;

DWidgetAction::DWidgetAction(QWidget *parent)
    : QWidgetAction(parent)
    , m_widget(parent)
{
}

QWidget *DWidgetAction::createWidget(QWidget *parent)
{
    m_widget->setParent(parent);

    return m_widget;
}
