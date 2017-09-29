#ifndef SYSTEMINFOMODEL_H
#define SYSTEMINFOMODEL_H

#include "networkdevicemodel.h"

#include <QObject>

class SystemInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit SystemInfoModel(QObject *parent = 0);
    NetworkDeviceModel * deviceByName(const QString &name);

signals:
    void requestDeviceAdded(NetworkDeviceModel *dev);
    void requestDeviceRemoved(const QString &name);

public slots:
    void addDevice(NetworkDeviceModel *dev);
    void removeDevice(const QString &name);

private:
    QList<NetworkDeviceModel*> m_devices;
};

#endif // SYSTEMINFOMODEL_H
