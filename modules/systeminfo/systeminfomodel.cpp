#include "systeminfomodel.h"

SystemInfoModel::SystemInfoModel(QObject *parent) : QObject(parent)
{

}

NetworkDeviceModel *SystemInfoModel::deviceByName(const QString &name)
{
    for (NetworkDeviceModel * dev : m_devices)
        if (dev->name() == name)
            return dev;

    return nullptr;
}

void SystemInfoModel::addDevice(NetworkDeviceModel *dev)
{
    if (m_devices.contains(dev))
        return;

    m_devices.append(dev);

    emit requestDeviceAdded(dev);
}

void SystemInfoModel::removeDevice(const QString &name)
{
    NetworkDeviceModel *dev = deviceByName(name);

    if (dev) {
        emit requestDeviceRemoved(name);
        m_devices.removeOne(dev);
        delete dev;
    }
}
