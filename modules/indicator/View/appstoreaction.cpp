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

#include "appstoreaction.h"
#include "../indicatormodel.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QEvent>
#include <QPainter>

using namespace dtb;
using namespace dtb::indicator;

AppstoreAction::AppstoreAction(QWidget *parent)
    : QWidgetAction(parent)
    , m_widget(new QWidget)
    , m_updateLbl(new QLabel)
    , m_enter(false)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->setContentsMargins(27, 0, 25, 0);

    QLabel *title = new QLabel("App Store");

    layout->addWidget(title, 0, Qt::AlignLeft);
    layout->addWidget(m_updateLbl, 0, Qt::AlignRight);

    m_updateLbl->setAlignment(Qt::AlignCenter);

    m_updateLbl->installEventFilter(this);
    m_widget->installEventFilter(this);

    m_widget->setFixedHeight(28);

    m_widget->setLayout(layout);
}

void AppstoreAction::setModel(IndicatorModel *model)
{
    m_model = model;

    connect(model, &IndicatorModel::appsListChanged, this, &AppstoreAction::onUpdatesChanged);

    onUpdatesChanged(model->appslist());
}

QWidget *AppstoreAction::createWidget(QWidget *parent)
{
    m_widget->setParent(parent);

    return m_widget;
}

bool AppstoreAction::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_updateLbl) {
        if (event->type() == QEvent::Paint) {
            QPainter painter(m_updateLbl);

            painter.setOpacity(m_enter ? 1.0 : 0.85);

            painter.setBrush(QColor(181, 181, 181, 0.3 * 255));
            painter.setPen(Qt::NoPen);

            QFont font = qApp->font();
            QFontMetrics fm(font);
            int h = (m_updateLbl->height() - fm.height()) / 2 - 2;
            painter.drawRoundRect(m_updateLbl->rect().marginsRemoved(QMargins(0, h, 0, h)), 10, 10);
        }
    }

    if (watched == m_widget) {
        if (event->type() == QEvent::Paint) {
            QPainter painter(m_widget);
            painter.fillRect(m_widget->rect(), m_enter ? QColor("#0b8cff") : QColor(0, 0, 0, 0));
        }
        if (event->type() == QEvent::Enter) {
            m_enter = true;
            m_widget->update();
            m_updateLbl->update();
        }
        if (event->type() == QEvent::Leave) {
            m_enter = false;
            m_widget->update();
            m_updateLbl->update();
        }
    }
return false;
    return QWidgetAction::eventFilter(watched, event);
}

void AppstoreAction::onUpdatesChanged(const QStringList &list)
{
    m_updateLbl->setText(tr("%1 update(s)").arg(list.count()));

    QFont font = qApp->font();
    QFontMetrics fm(font);

    m_updateLbl->setFixedWidth(fm.width(m_updateLbl->text()) + 8);
}
