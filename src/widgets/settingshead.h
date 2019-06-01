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

#ifndef SETTINGSHEAD_H
#define SETTINGSHEAD_H

#include "widgets/settingsitem.h"
#include <QPushButton>

namespace dtb {
namespace widgets {

class NormalLabel;
class SettingsHead : public SettingsItem
{
    Q_OBJECT

public:
    enum State
    {
        Edit,
        Cancel,
    };

public:
    explicit SettingsHead(QFrame *parent = 0);

    void setTitle(const QString& title);
    void setEditEnable(bool state = true);

public Q_SLOTS:
    void toEdit();
    void toCancel();

Q_SIGNALS:
    void editChanged(bool edit);

private Q_SLOTS:
    void refershButton();

private:
    NormalLabel *m_title;
    QPushButton *m_edit;
    QPushButton *m_cancel;

    State m_state;
};

}
}

#endif // SETTINGSHEAD_H
