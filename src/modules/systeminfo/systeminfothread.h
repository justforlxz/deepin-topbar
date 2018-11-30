#ifndef SYSTEMINFOTHREAD_H
#define SYSTEMINFOTHREAD_H

#include "systeminfomodel.h"
#include <QThread>
#include <QFile>
#include <QVariant>
#include <QDBusObjectPath>

namespace dtb {
namespace systeminfo {
class SysteminfoThread : public QThread
{
    Q_OBJECT
public:
    explicit SysteminfoThread(SystemInfoModel *model, QObject *parent = 0);

protected:
    void run() Q_DECL_OVERRIDE;

private slots:
    void onNetworkPropertyChanged(QVariantMap m);
    void onConnectChanged(const QDBusObjectPath &path);
    void onActiveChanged(const QVariant &value);
    void onGetDeviceName(const QVariant &device);

private:
    void getCpuTime(unsigned long long &workTime, unsigned long long &totalTime);

private:
    SystemInfoModel *m_model;
    QFile *m_rx;
    QFile *m_tx;
    quint64 old_tx;
    quint64 old_rx;
    QFile *m_statFile;
};
}
}

#endif // SYSTEMINFOTHREAD_H
