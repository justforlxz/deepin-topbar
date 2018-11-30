#include "notifyhandle.h"

#include <QJsonDocument>
#include <QJsonObject>

NotifyHandle::NotifyHandle(QObject *parent) : QObject(parent)
{

}

void NotifyHandle::RecordAdded(const QString &record)
{
    QJsonObject obj = QJsonDocument::fromJson(record.toUtf8()).object();

    for (auto it = m_dataJsonArray.begin(); it != m_dataJsonArray.end(); ++it) {

    }
}

void NotifyHandle::NotificationClosed(uint id, uint ClosedReason)
{

}
