#include "networkdevice.h"

#include <QDebug>
#include <QJsonObject>

NetworkDevice::NetworkDevice(const NetworkType type, const QJsonObject &info)
    : m_type(type),
      m_infoObj(info)
{
    m_devicePath = info.value("Path").toString();
}

bool NetworkDevice::operator==(const QString &path) const
{
    return m_devicePath == path;
}

bool NetworkDevice::operator==(const NetworkDevice &device) const
{
    return m_devicePath == device.m_devicePath;
}

NetworkDevice::NetworkState NetworkDevice::state() const
{
    return NetworkState(m_infoObj.value("State").toInt());
}

NetworkDevice::NetworkType NetworkDevice::type() const
{
    return m_type;
}

const QString NetworkDevice::path() const
{
    return m_devicePath;
}

const QDBusObjectPath NetworkDevice::dbusPath() const
{
    return QDBusObjectPath(m_devicePath);
}

const QString NetworkDevice::hwAddress() const
{
    return m_infoObj.value("HwAddress").toString();
}

const QString NetworkDevice::vendor() const
{
    return m_infoObj.value("Vendor").toString();
}

const QString NetworkDevice::activeAp() const
{
    return m_infoObj.value("ActiveAp").toString();
}

NetworkDevice::NetworkType NetworkDevice::deviceType(const QString &type)
{
    if (type == "bt")
        return NetworkDevice::Bluetooth;
    if (type == "generic")
        return NetworkDevice::Generic;
    if (type == "wired")
        return NetworkDevice::Wired;
    if (type == "wireless")
        return NetworkDevice::Wireless;
    if (type == "bridge")
        return NetworkDevice::Bridge;

    Q_ASSERT(false);

    return NetworkDevice::None;
}
