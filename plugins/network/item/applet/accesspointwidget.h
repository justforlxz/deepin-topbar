#ifndef ACCESSPOINTWIDGET_H
#define ACCESSPOINTWIDGET_H

#include "accesspoint.h"
#include "networkdevice.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDBusObjectPath>

#include <dimagebutton.h>
#include <dpicturesequenceview.h>

class AccessPointWidget : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(bool active READ active DESIGNABLE true)

public:
    explicit AccessPointWidget(const AccessPoint &ap);

    bool active() const;
    void setActiveState(const NetworkDevice::NetworkState state);

signals:
    void requestActiveAP(const QDBusObjectPath &apPath, const QString &ssid) const;
    void requestDeactiveAP(const AccessPoint &ap) const;

private:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void setStrengthIcon(const int strength);

private slots:
    void ssidClicked();
    void disconnectBtnClicked();

private:
    NetworkDevice::NetworkState m_activeState;

    AccessPoint m_ap;
    QPushButton *m_ssidBtn;
    Dtk::Widget::DPictureSequenceView *m_indicator;
    Dtk::Widget::DImageButton *m_disconnectBtn;
    QLabel *m_securityIcon;
    QLabel *m_strengthIcon;
};

#endif // ACCESSPOINTWIDGET_H
