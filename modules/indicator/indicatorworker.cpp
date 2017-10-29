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
    , m_checkUpdateJob(nullptr)
    , m_managerInter(new ManagerInter("com.deepin.lastore", "/com/deepin/lastore", QDBusConnection::systemBus(), this))
    , m_updateInter(new UpdateInter("com.deepin.lastore", "/com/deepin/lastore", QDBusConnection::systemBus(), this))
{
    m_managerInter->setSync(false);
    m_updateInter->setSync(false);

    connect(m_updateInter, &UpdateInter::UpdatableAppsChanged, m_model, &IndicatorModel::setAppslist, Qt::UniqueConnection);

    checkUpdates();
}

void IndicatorWorker::checkUpdates()
{
    if (m_checkUpdateJob)
        return;

    QDBusPendingCall call = m_managerInter->UpdateSource();
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, [this, call] {
        if (!call.isError()) {
            QDBusReply<QDBusObjectPath> reply = call.reply();
            const QString jobPath = reply.value().path();
            setCheckUpdatesJob(jobPath);
        }
    });
}

void IndicatorWorker::setCheckUpdatesJob(const QString &jobPath)
{
    if (m_checkUpdateJob)
        return;

    m_checkUpdateJob = new JobInter("com.deepin.lastore", jobPath, QDBusConnection::systemBus(), this);
    connect(m_checkUpdateJob, &__Job::StatusChanged, [this] (const QString & status) {
        if (status == "failed") {
            qWarning() << "check for updates job failed";
            m_managerInter->CleanJob(m_checkUpdateJob->id());
        } else if (status == "success" || status == "succeed"){
            m_checkUpdateJob->deleteLater();
            m_checkUpdateJob = nullptr;

            m_updateInter->updatableApps();
        }
    });
}
