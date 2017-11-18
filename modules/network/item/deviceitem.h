#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include "../networkmanager.h"
#include "../../../frame/item/contentmodule.h"

#include <QWidget>
#include <QMenu>

namespace dtb {
namespace network {
class DeviceItem : public ContentModule
{
    Q_OBJECT
public:
    explicit DeviceItem(const QString &path);

    const QString path() const { return m_devicePath; }

    virtual NetworkDevice::NetworkType type() const = 0;
    virtual NetworkDevice::NetworkState state() const = 0;

protected:
    bool enabled() const;
    void setEnabled(const bool enable);
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

protected:
    const QString m_devicePath;

    NetworkManager *m_networkManager;
    QMenu *m_menu;
};
}
}

#endif // DEVICEITEM_H
