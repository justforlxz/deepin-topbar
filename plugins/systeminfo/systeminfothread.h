#ifndef SYSTEMINFOTHREAD_H
#define SYSTEMINFOTHREAD_H

#include "systeminfomodel.h"

#include <QThread>
#include <QFile>

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
    QFile *m_rx;
    QFile *m_tx;
    SystemInfoModel *m_model;
};

#endif // SYSTEMINFOTHREAD_H
