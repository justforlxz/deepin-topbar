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

#ifndef SETTINGSHEADERITEM_H
#define SETTINGSHEADERITEM_H

#include "widgets/settingsitem.h"

#include <QHBoxLayout>
#include <QLabel>

namespace dtb {
namespace widgets {

class SettingsHeaderItem : public SettingsItem
{
    Q_OBJECT

public:
    explicit SettingsHeaderItem(QWidget *parent = 0);

    QLabel *textLabel() const { return m_headerText; }
    QHBoxLayout *layout() const { return m_mainLayout; }

    void setTitle(const QString &title);
    void setRightWidget(QWidget *widget);

private:
    QHBoxLayout *m_mainLayout;
    QLabel *m_headerText;
};

}
}

#endif // SETTINGSHEADERITEM_H
