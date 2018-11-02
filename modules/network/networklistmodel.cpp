#include "networklistmodel.h"

#include <QDebug>
#include <QSize>

using namespace dtb;
using namespace dtb::network;

NetworkListModel::NetworkListModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_currentWirelessDevice(nullptr)
{

}

void NetworkListModel::setDeviceList(const QMap<QString, dde::network::NetworkDevice *> list)
{
    m_wiredList.clear();
    m_wirelessList.clear();

    for (auto it = list.constBegin(); it != list.constEnd(); it++) {
        if (it.value()->type() == dde::network::NetworkDevice::Wired) {
            m_wiredList[it.key()] = static_cast<dde::network::WiredDevice*>(it.value());
        }
        else {
            dde::network::WirelessDevice *device = static_cast<dde::network::WirelessDevice*>(it.value());
            m_wirelessList[it.key()] = device;

            // set default wireless device
            if (!m_currentWirelessDevice) m_currentWirelessDevice = device;

            connect(device, &dde::network::WirelessDevice::apAdded, this, &NetworkListModel::APAdded);
            connect(device, &dde::network::WirelessDevice::apRemoved, this, &NetworkListModel::APRemoved);
            connect(device, &dde::network::WirelessDevice::apInfoChanged, this, &NetworkListModel::APPropertiesChanged);

            for (auto ap : device->apList()) {
                emit device->apAdded(ap.toObject());
            }
        }
    }

    // refresh all info
}

int NetworkListModel::rowCount(const QModelIndex &parent) const
{
    if (!m_currentWirelessDevice) {
        return 0;
    }

    return m_apMap[m_currentWirelessDevice].size();
}

QVariant NetworkListModel::data(const QModelIndex &index, int role) const
{
    if (!m_currentWirelessDevice) return QVariant();

    const int row { index.row() };

    switch (role) {
    case NameRole:
        return m_apMap[m_currentWirelessDevice][row].ssid();
        break;
    case SizeRole:
        return QSize(400, 50);
        break;
    default:
        break;
    }

    return QVariant();
}

void NetworkListModel::onActivateConnectChanged()
{

}

void NetworkListModel::deviceStateChanged()
{

}

void NetworkListModel::APAdded(const QJsonObject &obj)
{
    const AccessPoint ap(obj);
    dde::network::WirelessDevice* dev = static_cast<dde::network::WirelessDevice*>(sender());
    if (m_apMap[dev].contains(ap)) return;

    m_apMap[dev] << std::move(ap);

    // refresh
    emit layoutChanged();
}

void NetworkListModel::APRemoved(const QJsonObject &obj)
{
    const AccessPoint ap(obj);

    dde::network::WirelessDevice* dev = static_cast<dde::network::WirelessDevice*>(sender());
    m_apMap[dev].removeOne(ap);

    // refresh
    emit layoutChanged();
}

void NetworkListModel::APPropertiesChanged(const QJsonObject &apInfo)
{
    const AccessPoint ap(apInfo);

    dde::network::WirelessDevice* dev = static_cast<dde::network::WirelessDevice*>(sender());

    for (int i = 0; i != m_apMap[dev].size(); ++i) {
        if (m_apMap[dev][i] == ap) {
            m_apMap[dev][i] = ap;
            break;
        }
    }

    // refresh
    const QModelIndex i = index(m_apMap[dev].indexOf(ap));

    emit dataChanged(i, i);
}
