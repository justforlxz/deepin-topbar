#include "systeminfothread.h"
#include "networkdevicemodel.h"
#include <QFile>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>

SysteminfoThread::SysteminfoThread(SystemInfoModel *model, QObject *parent) :
    QThread(parent),
    m_model(model)
{
    m_tx = new QFile(this);
    m_rx = new QFile(this);

    old_rx = 0;
    old_tx = 0;

    QDBusConnection *dbus = new QDBusConnection(QDBusConnection::connectToBus(QDBusConnection::SystemBus, "org.freedesktop.NetworkManager"));
    QDBusInterface *network = new QDBusInterface("org.freedesktop.NetworkManager",
                                                 "/org/freedesktop/NetworkManager",
                                                 "org.freedesktop.NetworkManager",
                                                 *dbus,
                                                 this);

    QDBusConnection::systemBus().connect("org.freedesktop.NetworkManager",
                                         "/org/freedesktop/NetworkManager",
                                         "org.freedesktop.NetworkManager",
                                         "PropertiesChanged",
                                         "a{sv}",
                                         this,
                                         SLOT(onNetworkPropertyChanged(QVariantMap)));

    const QDBusObjectPath &path = qvariant_cast<QDBusObjectPath>(network->property("PrimaryConnection"));
    onConnectChanged(path);
}

void SysteminfoThread::run()
{
    for (;;) {
        Q_ASSERT(m_tx);
        Q_ASSERT(m_rx);

        if ((m_tx->fileName().isEmpty() || m_rx->fileName().isEmpty())) {
            msleep(1000);
            continue;
        }

        m_tx->open(QIODevice::ReadOnly | QIODevice::Text);
        m_rx->open(QIODevice::ReadOnly | QIODevice::Text);

        old_tx = QString(m_tx->readAll()).remove("\n").toULongLong();
        old_rx = QString(m_rx->readAll()).remove("\n").toULongLong();

        m_tx->close();
        m_rx->close();

        msleep(1000);

        m_tx->open(QIODevice::ReadOnly | QIODevice::Text);
        m_rx->open(QIODevice::ReadOnly | QIODevice::Text);

        emit networkSpeedChanged(QString(m_tx->readAll()).remove("\n").toULongLong() - old_tx,
                                 QString(m_rx->readAll()).remove("\n").toULongLong() - old_rx);

        m_tx->close();
        m_rx->close();

        continue;
    }
    msleep(1000);
}

void SysteminfoThread::onNetworkPropertyChanged(QVariantMap m)
{
    QDBusObjectPath path = qvariant_cast<QDBusObjectPath>(m["PrimaryConnection"]);
    if (path.path().isEmpty())
        return;

    qDebug() << "Network PrimaryConnect change to: " << path.path();

    onConnectChanged(path);
}

void SysteminfoThread::onActiveChanged(const QVariant &value)
{
    QList<QDBusObjectPath> list = qvariant_cast<QList<QDBusObjectPath>>(value);
    const QDBusObjectPath &path = list.first();
    if (path.path().isEmpty())
        return;

    qDebug() << "Network Active change to: " << path.path();

    QDBusConnection dbus(QDBusConnection::connectToBus(QDBusConnection::SystemBus, "org.freedesktop.NetworkManager"));
    QDBusInterface network("org.freedesktop.NetworkManager",
                           path.path(),
                           "org.freedesktop.NetworkManager.Device",
                           dbus,
                           this);

    onGetDeviceName(network.property("Interface"));
}

void SysteminfoThread::onConnectChanged(const QDBusObjectPath &path)
{
    QDBusConnection dbus(QDBusConnection::connectToBus(QDBusConnection::SystemBus, "org.freedesktop.NetworkManager"));
    QDBusInterface network("org.freedesktop.NetworkManager",
                           path.path(),
                           "org.freedesktop.NetworkManager.Connection.Active",
                           dbus,
                           this);

    qDebug() << "Network Connect change to: " << path.path();

    // get device name
    onActiveChanged(network.property("Devices"));
}

void SysteminfoThread::onGetDeviceName(const QVariant &device)
{
    const QString &name = device.toString();

    if (name.isEmpty())
        return;

    qDebug() << "Device change to: " << name;

    const QString &r = "/sys/class/net/" + name + "/statistics/rx_bytes";
    const QString &t = "/sys/class/net/" + name + "/statistics/tx_bytes";

    m_rx->setFileName(r);
    m_tx->setFileName(t);
}

