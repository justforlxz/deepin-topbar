#ifndef NETWORKDEVICEMODEL_H
#define NETWORKDEVICEMODEL_H

#include <QObject>

class NetworkDeviceModel : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDeviceModel(QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    QString ip() const;
    void setIp(const QString &ip);

    QString hardwareAddress() const;
    void setHardwareAddress(const QString &hardwareAddress);

protected:
    bool operator ==(NetworkDeviceModel *dev);

signals:
    void requestIpChanged(const QString &ip);

private:
    QString m_name;
    QString m_ip;
    QString m_hardwareAddress;
};

#endif // NETWORKDEVICEMODEL_H
