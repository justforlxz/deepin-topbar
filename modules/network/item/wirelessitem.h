#ifndef WIRELESSITEM_H
#define WIRELESSITEM_H

#include "deviceitem.h"
#include "../networkdevice.h"
#include "applet/accesspointwidget.h"
#include "../widgets/fontlabel.h"
#include "../widgets/dactionlabel.h"

#include <dinputdialog.h>

DWIDGET_USE_NAMESPACE

namespace dtb {
namespace network {
class WirelessItem : public DeviceItem
{
    Q_OBJECT

public:
    explicit WirelessItem(const QString &path);
    ~WirelessItem();

    NetworkDevice::NetworkType type() const;
    NetworkDevice::NetworkState state() const;

signals:
    void activeAPChanged() const;

private slots:
    void init();
    void onActivateConnectChanged();
    void deviceEnabled(const QString &devPath, const bool enable);
    void deviceStateChanged();

    void APAdded(const QString &devPath, const QString &info);
    void APRemoved(const QString &devPath, const QString &info);
    void APPropertiesChanged(const QString &devPath, const QString &info);

    void loadAPList();
    void onActiveAPChanged();
    void updateAPList();
    void needSecrets(const QString &info);
    void pwdDialogAccepted();
    void pwdDialogCanceled();
    void activateAP(const QDBusObjectPath &apPath, const QString &ssid);
    void deactiveAP();

private:
    widgets::FontLabel *m_wirelessLbl;
    bool m_isConnected;
    NetworkDevice m_device;
    DBusNetwork *m_networkInter;
    NetworkDevice::NetworkState m_activeState;
    QList<AccessPoint> m_apList;
    AccessPoint m_activeAP;
    QTimer *m_updateAPTimer;
    Dtk::Widget::DInputDialog *m_pwdDialog;
    QString m_lastConnPath;
    QString m_lastConnSecurity;
    QList<AccessPointWidget*> m_apwLists;
    QList<widgets::DActionLabel*> m_acList;

    QAction *m_joinOther;
    QAction *m_preferences;
    QAction *m_separator;
};
}
}

#endif // WIRELESSITEM_H
