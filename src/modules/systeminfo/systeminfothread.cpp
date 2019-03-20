#include "systeminfothread.h"

#include <QFile>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDebug>
#include <proc/sysinfo.h>

using namespace dtb;
using namespace dtb::systeminfo;

SysteminfoThread::SysteminfoThread(SystemInfoModel *model, QObject *parent) :
    QThread(parent),
    m_model(model)
{
    m_tx = new QFile(this);
    m_rx = new QFile(this);

    m_statFile = new QFile(this);

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
        Q_ASSERT(m_statFile);

        // update cpu infos

        unsigned long long currentWorkTime = 0, prevWorkTime = 0;
        unsigned long long currentTotalTime = 0, prevTotalTime = 0;

        getCpuTime(prevWorkTime, prevTotalTime);

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

        getCpuTime(currentWorkTime, currentTotalTime);

        m_model->setCputime(
                static_cast<int>((currentWorkTime - prevWorkTime) * 100.0 / (currentTotalTime - prevTotalTime)));

        meminfo();
        auto memoryPercent = (kb_main_total - kb_main_available) * 100.0 / kb_main_total;
        auto swapPercent = kb_swap_used * 100.0 / kb_swap_total;
        emit m_model->memChanged(static_cast<int>(memoryPercent), static_cast<int>(swapPercent));
        m_tx->open(QIODevice::ReadOnly | QIODevice::Text);
        m_rx->open(QIODevice::ReadOnly | QIODevice::Text);

        emit m_model->networkSpeedChanged(QString(m_tx->readAll()).remove("\n").toULongLong() - old_tx,
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
    if (list.isEmpty())
        return;

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
//    ip r | grep default | sed 's/.*dev \([^ ]*\).*/\1/'
    const QString &name = device.toString();

    if (name.isEmpty())
        return;

    qDebug() << "Device change to: " << name;

    const QString &r = "/sys/class/net/" + name + "/statistics/rx_bytes";
    const QString &t = "/sys/class/net/" + name + "/statistics/tx_bytes";

    m_rx->setFileName(r);
    m_tx->setFileName(t);
}

void SysteminfoThread::getCpuTime(unsigned long long &workTime, unsigned long long &totalTime)
{
    m_statFile->setFileName("/proc/stat");

    if (!m_statFile->open(QIODevice::ReadOnly))
        Q_ASSERT(true);

    QString buffer = m_statFile->readAll();
    QStringList list = buffer.split("\n").filter(QRegExp("^cpu "));
    QString line = list.first();
    QStringList lines = line.trimmed().split(QRegExp("\\s+"));

    unsigned long long user = lines.at(1).toLong();
    unsigned long long nice = lines.at(2).toLong();
    unsigned long long system = lines.at(3).toLong();
    unsigned long long idle = lines.at(4).toLong();
    unsigned long long iowait = lines.at(5).toLong();
    unsigned long long irq = lines.at(6).toLong();
    unsigned long long softirq = lines.at(7).toLong();
    unsigned long long steal = lines.at(8).toLong();
    //unsigned long long guest = lines.at(9).toLong();
    //unsigned long long guestnice = lines.at(10).toLong();

    workTime = user + nice + system;
    totalTime = user + nice + system + idle + iowait + irq + softirq + steal;

    m_statFile->close();
}
