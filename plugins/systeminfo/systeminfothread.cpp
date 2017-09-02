#include "systeminfothread.h"
#include "networkdevicemodel.h"
#include <QFile>
#include <QNetworkInterface>

SysteminfoThread::SysteminfoThread(SystemInfoModel *model, QObject *parent) :
    QThread(parent),
    m_model(model)
{
    m_tx = new QFile(this);
    m_rx = new QFile(this);

    old_rx = 0;
    old_tx = 0;
}

void SysteminfoThread::run()
{
    for (;;) {
        QString device;
        foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
            if (!device.isEmpty())
                break;

            if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
                foreach (QNetworkAddressEntry entry, interface.addressEntries()) {
                    if ( interface.hardwareAddress() != "00:00:00:00:00:00" && entry.ip().toString().contains(".")) {
//                         qDebug() << interface.name() + " "+ entry.ip().toString() +" " + interface.hardwareAddress();

//                        NetworkDeviceModel *model = m_model->deviceByName(interface.name());

//                        if (!model) {
//                            model = new NetworkDeviceModel;
//                            model->setName(interface.name());
//                            model->setIp(entry.ip().toString());
//                            model->setHardwareAddress(interface.hardwareAddress());
//                            m_model->addDevice(model);
//                        } else {
//                            model->setName(interface.name());
//                            model->setIp(entry.ip().toString());
//                            model->setHardwareAddress(interface.hardwareAddress());
//                        }

                        const QString &r = "/sys/class/net/" + interface.name() + "/statistics/rx_bytes";
                        const QString &t = "/sys/class/net/" + interface.name() + "/statistics/tx_bytes";

                        if (r != m_rx->fileName() && t != m_tx->fileName() && device != interface.name()) {
                            device = interface.name();
                            m_rx->setFileName(r);
                            m_tx->setFileName(t);
                        }

                        break;
                    }
                }
            }
        }

        Q_ASSERT(m_tx);
        Q_ASSERT(m_rx);

        m_tx->open(QIODevice::ReadOnly | QIODevice::Text);
        m_rx->open(QIODevice::ReadOnly | QIODevice::Text);

        old_tx = QString(m_tx->readAll()).remove("\n").toULongLong();
        old_rx = QString(m_rx->readAll()).remove("\n").toULongLong();

        msleep(1000);

        m_tx->flush();
        m_rx->flush();

        emit networkSpeedChanged(QString(m_tx->readAll()).remove("\n").toULongLong() - old_tx,
                                 QString(m_rx->readAll()).remove("\n").toULongLong() - old_rx);

        m_tx->close();
        m_rx->close();

        continue;
    }
    msleep(1000);
}
