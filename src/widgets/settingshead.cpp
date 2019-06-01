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

#include "widgets/settingshead.h"
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>

#include "widgets/labels/normallabel.h"

namespace dtb {
namespace widgets {

SettingsHead::SettingsHead(QFrame *parent)
    : SettingsItem(parent),

      m_title(new NormalLabel),
      m_edit(new QPushButton),
      m_cancel(new QPushButton),

      m_state(Cancel)
{
    m_title->setObjectName("SettingsHeadTitle");

    m_edit->setFlat(true);
    m_cancel->setFlat(true);

    // can not translate correctly just using tr()
    m_edit->setText(qApp->translate("SettingsHead", "Edit"));
    m_edit->setVisible(false);

    // same as above
    m_cancel->setText(qApp->translate("SettingsHead", "Cancel"));
    m_cancel->setVisible(false);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(20, 0, 10, 0);
    mainLayout->addWidget(m_title);
    mainLayout->addStretch();
    mainLayout->addWidget(m_edit);
    mainLayout->addWidget(m_cancel);

    setFixedHeight(24);
    setLayout(mainLayout);

    connect(m_edit, &QPushButton::clicked, this, &SettingsHead::toEdit);
    connect(m_cancel, &QPushButton::clicked, this, &SettingsHead::toCancel);
}

void SettingsHead::setTitle(const QString &title)
{
    m_title->setText(title);
    m_edit->setAccessibleName(title);
}

void SettingsHead::setEditEnable(bool state)
{
    // reset state
    toCancel();

    m_edit->setVisible(state && m_state == Cancel);
    m_cancel->setVisible(state && m_state == Edit);
}

void SettingsHead::toEdit()
{
    m_state = Edit;
    refershButton();

    Q_EMIT editChanged(true);
}

void SettingsHead::toCancel()
{
    m_state = Cancel;
    refershButton();

    Q_EMIT editChanged(false);
}

void SettingsHead::refershButton()
{
    m_edit->setVisible(m_state == Cancel);
    m_cancel->setVisible(m_state == Edit);
}

}

}
