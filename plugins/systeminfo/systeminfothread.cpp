#include "systeminfothread.h"
#include "networkdevicemodel.h"
#include <QFile>
#include <QNetworkInterface>

SysteminfoThread::SysteminfoThread(SystemInfoModel *model, QObject *parent) :
    m_model(model)
{
    m_rx = nullptr;
    m_tx = nullptr;
}

void SysteminfoThread::run()
{
    quint64 old_tx;
    quint64 old_rx;

    for (;;) {
        QString device;
        foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
            if (!device.isEmpty())
                break;

            if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
                    if ( interface.hardwareAddress() != "00:00:00:00:00:00" && entry.ip().toString().contains(".")) {
//                         qDebug() << interface.name() + " "+ entry.ip().toString() +" " + interface.hardwareAddress();

                        NetworkDeviceModel *model = m_model->deviceByName(interface.name());

                        if (!model) {
                            model = new NetworkDeviceModel;
                            model->setName(interface.name());
                            model->setIp(entry.ip().toString());
                            model->setHardwareAddress(interface.hardwareAddress());
                            m_model->addDevice(model);
                        } else {
                            model->setName(interface.name());
                            model->setIp(entry.ip().toString());
                            model->setHardwareAddress(interface.hardwareAddress());
                        }

                        device = interface.name();
                        if (m_rx) {
                            m_rx->deleteLater();
                            m_rx = nullptr;
                        }
                        if (m_tx) {
                            m_tx->deleteLater();
                            m_tx = nullptr;
                        }
                        m_rx = new QFile("/sys/class/net/" + interface.name() + "/statistics/rx_bytes");
                        m_tx = new QFile("/sys/class/net/" + interface.name() + "/statistics/tx_bytes");
                        break;
                    }
                }
            }
        }

        if (m_rx && m_tx) {
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
