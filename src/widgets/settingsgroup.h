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

#ifndef SETTINGSGROUP_H
#define SETTINGSGROUP_H

#include <QFrame>
#include <QTimer>

#include "widgets/translucentframe.h"

class QVBoxLayout;

namespace dtb {
namespace widgets {

class SettingsItem;

class SettingsGroup : public TranslucentFrame
{
    Q_OBJECT

public:
    explicit SettingsGroup(QFrame *parent = 0);
    explicit SettingsGroup(const QString &title, QFrame *parent = 0);
    ~SettingsGroup();

    SettingsItem* getItem(int index);
    void insertItem(const int index, SettingsItem * item);
    void appendItem(SettingsItem * item);
    void removeItem(SettingsItem * item);
    void moveItem(SettingsItem *item, const int index);
    void setSpacing(const int spaceing);

    int itemCount() const;
    void clear();

private:
    bool eventFilter(QObject *, QEvent *event);
    void updateHeadTail();

private Q_SLOTS:
    void updateHeight();

private:
    QVBoxLayout *m_layout;

    QTimer *m_updateHeightTimer;
    QTimer *m_updateHeadTailTimer;
};

}
}

#endif // SETTINGSGROUP_H
