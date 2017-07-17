#ifndef SYSTEMINFOTHREAD_H
#define SYSTEMINFOTHREAD_H

#include "DBus/org_freedesktop_networkmanager.h"
#include "DBus/org_freedesktop_networkmanager_activeconnection.h"
#include "DBus/org_freedesktop_networkmanager_device.h"

#include <QThread>

using NetworkManager = org::freedesktop::NetworkManager;
using ActiveConnect = org::freedesktop::networkmanager::connection::Active;
using Device = org::freedesktop::networkmanager::Device;

class SysteminfoThread : public QThread
{
    Q_OBJECT
public:
    explicit SysteminfoThread(QObject *parent = 0);

signals:
    void networkSpeedChanged(const int tx, const int rx);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    NetworkManager *m_networkmanager;
    ActiveConnect *m_activeConnect;
    Device *m_device;
    QFile *m_rx;
    QFile *m_tx;
};

#endif // SYSTEMINFOTHREAD_H
