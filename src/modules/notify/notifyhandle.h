#ifndef NOTIFYHANDLE_H
#define NOTIFYHANDLE_H

#include <QObject>
#include <QJsonArray>

class NotifyHandle : public QObject
{
    Q_OBJECT
public:
    explicit NotifyHandle(QObject *parent = nullptr);

    void RecordAdded(const QString &record);
    void NotificationClosed(uint id, uint ClosedReason);

signals:

public slots:

private:
    std::map<QString, QJsonArray> m_dataJsonArray;
};

#endif // NOTIFYHANDLE_H
