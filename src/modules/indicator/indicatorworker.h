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

#ifndef INDICATORWORKER_H
#define INDICATORWORKER_H

#include <com_deepin_lastore_updater.h>

#include <QObject>

using UpdateInter=com::deepin::lastore::Updater;

namespace dtb {
namespace indicator {

class IndicatorModel;
class IndicatorWorker : public QObject
{
    Q_OBJECT
public:
    explicit IndicatorWorker(IndicatorModel* model, QObject *parent = nullptr);

private:
    IndicatorModel *m_model;
    UpdateInter* m_updateInter;
};
}
}

#endif // INDICATORWORKER_H
