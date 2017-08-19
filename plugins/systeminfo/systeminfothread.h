#ifndef SYSTEMINFOTHREAD_H
#define SYSTEMINFOTHREAD_H

#include "systeminfomodel.h"
#include <memory>
#include <QThread>
#include <QFile>

using namespace std;

class SysteminfoThread : public QThread
{
    Q_OBJECT
public:
    explicit SysteminfoThread(SystemInfoModel *model, QObject *parent = 0);

signals:
    void networkSpeedChanged(const quint64 tx, const quint64 rx);

protected:
    void run() Q_DECL_OVERRIDE;

private:
    SystemInfoModel *m_model;
    static unique_ptr<QFile> m_rx;
    static unique_ptr<QFile> m_tx;
};

#endif // SYSTEMINFOTHREAD_H
