#include "systeminfothread.h"
#include <QDBusConnection>
#include <QDBusObjectPath>
#include <QFile>

SysteminfoThread::SysteminfoThread(QObject *parent) : QThread(parent)
{
    m_networkmanager = nullptr;
    m_activeConnect = nullptr;
    m_device = nullptr;
    m_rx = nullptr;
    m_tx = nullptr;

    m_networkmanager = new NetworkManager("org.freedesktop.NetworkManager", "/org/freedesktop/NetworkManager", QDBusConnection::systemBus(), this);
    m_networkmanager->setSync(false);
    connect(m_networkmanager, &NetworkManager::PrimaryConnectionChanged, this, [=] (const QDBusObjectPath & connectPath) {
        if (m_activeConnect) {
            m_activeConnect->deleteLater();
            m_activeConnect = nullptr;
        }

        m_activeConnect = new ActiveConnect("org.freedesktop.NetworkManager",
                                            connectPath.path(),
                                            QDBusConnection::systemBus(), this);

        m_activeConnect->setSync(false);

        connect(m_activeConnect, &ActiveConnect::DevicesChanged, this, [=] (const QList<QDBusObjectPath> & devicePath) {
            if (m_device) {
                m_device->deleteLater();
                m_device = nullptr;
            }

            m_device = new Device("org.freedesktop.NetworkManager",
                                  devicePath.first().path(),
                                  QDBusConnection::systemBus(), this);

            m_device->setSync(false);

            connect(m_device, &Device::InterfaceChanged, this, [=] (const QString &value) {
                if (m_rx) {
                    m_rx->deleteLater();
                    m_rx = nullptr;
                }

                if (m_tx) {
                    m_tx->deleteLater();
                    m_tx = nullptr;
                }

                m_rx = new QFile("/sys/class/net/" + value + "/statistics/rx_bytes");
                m_tx = new QFile("/sys/class/net/" + value + "/statistics/tx_bytes");

            });

            m_device->interface();
        });

        m_activeConnect->devices();
    });

    m_networkmanager->primaryConnection();
}

void SysteminfoThread::run()
{
    quint64 old_tx;
    quint64 old_rx;

    for (;;) {
        if (m_device && m_rx && m_tx) {
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
}
