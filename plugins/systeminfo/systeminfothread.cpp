#include "systeminfothread.h"
#include "networkdevicemodel.h"
#include <QFile>
#include <QNetworkInterface>

std::unique_ptr<QFile> SysteminfoThread::m_rx(nullptr);
std::unique_ptr<QFile> SysteminfoThread::m_tx(nullptr);

SysteminfoThread::SysteminfoThread(SystemInfoModel *model, QObject *parent) :
    QThread(parent),
    m_model(model)
{
    if (!m_rx.get()) {
        QFile *file = new QFile;
        m_rx.reset(file);
    }

    if (!m_tx.get()) {
        QFile *file = new QFile;
        m_tx.reset(file);
    }
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

                        QFile *rx = m_rx.get();
                        if (rx)
                            rx->setFileName("/sys/class/net/" + interface.name() + "/statistics/rx_bytes");

                        QFile *tx = m_tx.get();
                        if (tx)
                            tx->setFileName("/sys/class/net/" + interface.name() + "/statistics/tx_bytes");

                        break;
                    }
                }
            }
        }

        QFile *rx = m_rx.get();
        QFile *tx = m_tx.get();

        if (rx && tx) {
            tx->open(QIODevice::ReadOnly | QIODevice::Text);
            rx->open(QIODevice::ReadOnly | QIODevice::Text);

            old_tx = QString(tx->readAll()).remove("\n").toULongLong();
            old_rx = QString(m_rx->readAll()).remove("\n").toULongLong();

            tx->close();
            rx->close();

            msleep(1000);

            tx->open(QIODevice::ReadOnly | QIODevice::Text);
            rx->open(QIODevice::ReadOnly | QIODevice::Text);

            emit networkSpeedChanged(QString(m_tx->readAll()).remove("\n").toULongLong() - old_tx,
                                     QString(m_rx->readAll()).remove("\n").toULongLong() - old_rx);

            tx->close();
            rx->close();

            continue;
        }
        msleep(1000);
    }
}
