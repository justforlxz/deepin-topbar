#ifndef WIRELESSAPPLET_H
#define WIRELESSAPPLET_H

#include "devicecontrolwidget.h"
#include "accesspoint.h"
#include "../../networkdevice.h"
#include "../../dbus/dbusnetwork.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QList>
#include <QTimer>

#include <dinputdialog.h>
#include <QCheckBox>

class WirelessList : public QScrollArea
{
    Q_OBJECT

public:
    explicit WirelessList(const QSet<NetworkDevice>::const_iterator &deviceIter, QWidget *parent = 0);
    ~WirelessList();

    NetworkDevice::NetworkState wirelessState() const;
    int activeAPStrgength() const;
    QWidget *controlPanel();

signals:
    void wirelessStateChanged(const NetworkDevice::NetworkState state) const;
    void activeAPChanged() const;

private:
    void setDeviceInfo(const int index);
    void loadAPList();

private slots:
    void init();
    void APAdded(const QString &devPath, const QString &info);
    void APRemoved(const QString &devPath, const QString &info);
    void APPropertiesChanged(const QString &devPath, const QString &info);
    void updateAPList();
    void deviceEnableChanged(const bool enable);
    void deviceStateChanged();
    void onActiveAPChanged();
    void pwdDialogAccepted();
    void pwdDialogCanceled();
    void deviceEnabled(const QString &devPath, const bool enable);
    void activateAP(const QDBusObjectPath &apPath, const QString &ssid);
    void deactiveAP();
    void needSecrets(const QString &info);

private:
    NetworkDevice m_device;

    AccessPoint m_activeAP;
    QList<AccessPoint> m_apList;

    QTimer *m_updateAPTimer;
    Dtk::Widget::DInputDialog *m_pwdDialog;
    QCheckBox *m_autoConnBox;

    QString m_lastConnPath;
    QString m_lastConnSecurity;

    QVBoxLayout *m_centralLayout;
    QWidget *m_centralWidget;
    DeviceControlWidget *m_controlPanel;
    DBusNetwork *m_networkInter;
};

#endif // WIRELESSAPPLET_H
