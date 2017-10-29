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

#ifndef SYSTEMLOGO_H
#define SYSTEMLOGO_H

#include "item/contentmodule.h"
#include "appstoreaction.h"
#include <QMenu>

namespace dtb {
namespace indicator {
class IndicatorModel;
class SystemLogo : public ContentModule
{
    Q_OBJECT
public:
    explicit SystemLogo(QWidget *parent = nullptr);

    QMenu *menu() const;

    void setModel(IndicatorModel *model);

signals:
    void requestForceQuit();

private slots:
    void handleAction(const int &action);
    void handleShutdownAction(const QString &action);

private:
    enum Action{
        About,
        Preference,
        Appstore,
        ForceQuit,
    };

private:
    QMenu *m_menu;
    IndicatorModel *m_model;
    AppstoreAction *m_appstore;
};
}
}

#endif // SYSTEMLOGO_H
