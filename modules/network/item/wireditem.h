#ifndef WIREDITEM_H
#define WIREDITEM_H

#include "deviceitem.h"

#include <QWidget>
#include <QTimer>
#include <QMenu>

namespace dtb {
namespace widgets {
class FontLabel;
}
namespace network {
class WiredItem : public DeviceItem
{
    Q_OBJECT

public:
    explicit WiredItem(const QString &path);

    NetworkDevice::NetworkType type() const override;
    NetworkDevice::NetworkState state() const override;

protected:
    void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;

private slots:
    void activeConnectionChanged();
    void deviceStateChanged(const NetworkDevice &device);
    void onDelayTimeOut();

private:
    bool m_connected;
    widgets::FontLabel *m_networkLbl;
    QTimer *m_delayTimer;
    QAction *m_preferences;
};
}
}

#endif // WIREDITEM_H
