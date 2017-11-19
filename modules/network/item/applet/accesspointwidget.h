#ifndef ACCESSPOINTWIDGET_H
#define ACCESSPOINTWIDGET_H

#include "accesspoint.h"
#include "../../networkdevice.h"
#include "../../../../widgets/fontlabel.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDBusObjectPath>

#include <dpicturesequenceview.h>

namespace dtb {
namespace network {
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
    void setStrengthIcon(const int strength);

protected:
    void enterEvent(QEvent *e) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *e) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private slots:
    void ssidClicked();
    void disconnectBtnClicked();

private:
    NetworkDevice::NetworkState m_activeState;

    AccessPoint m_ap;
    QPushButton *m_ssidBtn;
    Dtk::Widget::DPictureSequenceView *m_indicator;
    QFrame *m_connectedBtn;
    widgets::FontLabel *m_disconnectBtn;
    widgets::FontLabel *m_securityIcon;
    widgets::FontLabel *m_strengthIcon;
};
}
}

#endif // ACCESSPOINTWIDGET_H
