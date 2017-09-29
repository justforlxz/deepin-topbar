#include "networkdevicemodel.h"

NetworkDeviceModel::NetworkDeviceModel(QObject *parent) : QObject(parent)
{

}

QString NetworkDeviceModel::name() const
{
    return m_name;
}

void NetworkDeviceModel::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
}

QString NetworkDeviceModel::ip() const
{
    return m_ip;
}

void NetworkDeviceModel::setIp(const QString &ip)
{
    if (m_ip == ip)
        return;

    m_ip = ip;

    emit requestIpChanged(ip);
}

QString NetworkDeviceModel::hardwareAddress() const
{
    return m_hardwareAddress;
}

void NetworkDeviceModel::setHardwareAddress(const QString &hardwareAddress)
{
    if (m_hardwareAddress == hardwareAddress)
        return;

    m_hardwareAddress = hardwareAddress;
}

bool NetworkDeviceModel::operator ==(NetworkDeviceModel *dev)
{
    return m_name == dev->name();
}
