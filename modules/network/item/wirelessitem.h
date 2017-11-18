#ifndef WIRELESSITEM_H
#define WIRELESSITEM_H

#include "deviceitem.h"
#include "applet/wirelessapplet.h"
#include "../widgets/fontlabel.h"

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

private slots:
    void init();
    void onActivateConnectChanged();

private:
    widgets::FontLabel *m_wirelessLbl;
    bool m_isConnected;
    NetworkDevice m_device;
};
}
}

#endif // WIRELESSITEM_H
