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

#ifndef SEARCHMODULE_H
#define SEARCHMODULE_H

#include "interfaces/pluginsiteminterface.h"
#include "searchbutton.h"

#include <QObject>

namespace dtb {
namespace search {
class SearchModule : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    explicit SearchModule(QObject *parent = nullptr);

    const QString pluginName() const Q_DECL_OVERRIDE;

    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    SearchButton *m_btn;
};
}
}
#endif // SEARCHMODULE_H
