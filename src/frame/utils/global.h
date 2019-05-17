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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>

#define TOPHEIGHT 26
#define FRAMEHEIGHT 35
#define FONTSIZE 13

static const QStringList Module_list = {"systeminfo",
                                        "system-tray",
                                        "sound",
                                        "power",
                                        "network",
                                        "datetime",
                                        "search",
                                        "notify"
                                       };

class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);

signals:

public slots:
};

#endif // GLOBAL_H
