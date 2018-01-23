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

#include "searchmodule.h"
#include "../../frame/utils/global.h"

using namespace dtb;
using namespace dtb::search;

SearchModule::SearchModule(QObject *parent)
    : QObject(parent)
    , m_btn(new SearchButton)
{

}

const QString SearchModule::pluginName() const
{
    return QString("Search");
}

void SearchModule::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, pluginName());
}

QWidget *SearchModule::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_btn;
}

void SearchModule::setDefaultColor(PluginProxyInterface::DefaultColor color)
{
    Q_UNUSED(color);
}
