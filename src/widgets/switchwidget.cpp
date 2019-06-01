/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
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

#include "widgets/switchwidget.h"

#include <QHBoxLayout>

#include <QDebug>
#include <QMouseEvent>

#include "widgets/labels/normallabel.h"

DWIDGET_USE_NAMESPACE

namespace dtb {
namespace widgets {

SwitchWidget::SwitchWidget(QFrame *parent)
    : SwitchWidget(new NormalLabel, parent)
{

}

SwitchWidget::SwitchWidget(const QString &title, QFrame *parent) :
    SwitchWidget(new NormalLabel(title), parent)
{

}

SwitchWidget::SwitchWidget(QWidget *widget, QFrame *parent):
    SettingsItem(parent),
    m_leftWidget(widget),
    m_switchBtn(new DSwitchButton)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(20, 0, 10, 0);

    mainLayout->addWidget(m_leftWidget, 0, Qt::AlignVCenter);
    mainLayout->addStretch();
    mainLayout->addWidget(m_switchBtn, 0, Qt::AlignVCenter);

    setFixedHeight(36);
    setLayout(mainLayout);

    connect(m_switchBtn, &DSwitchButton::checkedChanged, this, &SwitchWidget::checkedChanged);
}

void SwitchWidget::setChecked(const bool checked)
{
    m_switchBtn->blockSignals(true);
    m_switchBtn->setChecked(checked);
    m_switchBtn->blockSignals(false);
}

void SwitchWidget::setTitle(const QString &title)
{
    QLabel *label = qobject_cast<QLabel*>(m_leftWidget);
    if (label) {
        label->setText(title);
    }

    setAccessibleName(title);
}

bool SwitchWidget::checked() const
{
    return m_switchBtn->checked();
}

void SwitchWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_switchBtn->geometry().contains(event->pos())) {
        Q_EMIT clicked();
    }

    return SettingsItem::mouseReleaseEvent(event);
}

}
}
