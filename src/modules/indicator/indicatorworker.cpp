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

#include "indicatorworker.h"
#include "indicatormodel.h"

using namespace dtb;
using namespace dtb::indicator;

IndicatorWorker::IndicatorWorker(IndicatorModel *model, QObject *parent)
    : QObject(parent)
    , m_model(model)
    , m_updateInter(new UpdateInter("com.deepin.lastore", "/com/deepin/lastore", QDBusConnection::systemBus(), this))
{
    m_updateInter->setSync(false);

    connect(m_updateInter, &UpdateInter::UpdatableAppsChanged, m_model, &IndicatorModel::setAppslist, Qt::UniqueConnection);

    m_updateInter->updatableApps();
}
