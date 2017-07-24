#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include "dbus/dbusnetwork.h"
#include "networkdevice.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    enum GlobalNetworkState {
        Unknown = 0,
        Asleep = 10,
        Disconnected = 20,
        Disconnecting = 30,
        Connecting = 40,
        ConnectedLocal = 50,
        ConnectedSite = 60,
        ConnectedGlobal = 70,
    };

public:
    static NetworkManager *instance(QObject *parent = nullptr);

    void init();

    GlobalNetworkState globalNetworkState() const;
    const NetworkDevice::NetworkTypes states() const;
    const NetworkDevice::NetworkTypes types() const;
    const QSet<NetworkDevice> deviceList() const;
    const QSet<QUuid> activeConnSet() const;
    const QSet<QString> activeDeviceSet() const { return m_activeDeviceSet; }

    NetworkDevice::NetworkState deviceState(const QString &path) const;
    bool deviceEnabled(const QString &path) const;
    void setDeviceEnabled(const QString path, const bool enable);
    const QString deviceHwAddr(const QString &path) const;
    const QString devicePath(const QString &path) const;
    const QJsonObject deviceConnInfo(const QString &path) const;
    const QSet<NetworkDevice>::const_iterator device(const QString &path) const;

signals:
    void globalNetworkStateChanged() const;
    void deviceAdded(const NetworkDevice &device) const;
    void deviceChanged(const NetworkDevice &device) const;
    void deviceRemoved(const NetworkDevice &device) const;
    void activeConnectionChanged(const QUuid &uuid) const;
    void networkStateChanged(const NetworkDevice::NetworkTypes &states) const;
    void deviceTypesChanged(const NetworkDevice::NetworkTypes &types) const;

private:
    explicit NetworkManager(QObject *parent = 0);


private slots:
    void reloadDevices();
    void reloadActiveConnections();
    void reloadNetworkState();

private:
    NetworkDevice::NetworkTypes m_states;
    NetworkDevice::NetworkTypes m_types;
    DBusNetwork *m_networkInter;

    QSet<NetworkDevice> m_deviceSet;
    QSet<QUuid> m_activeConnSet;
    QSet<QString> m_activeDeviceSet;

    static NetworkManager *INSTANCE;
};
#endif // NETWORKMANAGER_H
