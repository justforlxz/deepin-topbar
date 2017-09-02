#ifndef SYSTEMINFOTHREAD_H
#define SYSTEMINFOTHREAD_H

#include "systeminfomodel.h"
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
    QFile *m_rx;
    QFile *m_tx;
    quint64 old_tx;
    quint64 old_rx;
    QString m_rxFilePath;
    QString m_txFilePath;
};

#endif // SYSTEMINFOTHREAD_H
