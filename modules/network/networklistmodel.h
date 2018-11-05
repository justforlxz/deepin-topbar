#ifndef NETWORKLISTMODEL_H
#define NETWORKLISTMODEL_H

#include "item/applet/accesspoint.h"

#include <QObject>
#include <QAbstractListModel>
#include <NetworkDevice>
#include <WiredDevice>
#include <WirelessDevice>

namespace dtb {
namespace network {
class NetworkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit NetworkListModel(QObject *parent = nullptr);
    void setDeviceList(const QMap<QString, dde::network::NetworkDevice *> list);

    enum ListRole {
        NameRole = Qt::DisplayRole,
        SizeRole = Qt::SizeHintRole,
        HoverRole,
        IconRole,
        SecurityRole,
    };

    void setHoverIndex(const QModelIndex &index);

protected:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

private:
    void onActivateConnectChanged();
    void deviceStateChanged();
    void APAdded(const QJsonObject &obj);
    void APRemoved(const QJsonObject &obj);
    void APPropertiesChanged(const QJsonObject &apInfo);
    bool isSecurity(const QModelIndex &index) const;
    const QString icon(const QModelIndex &index) const;

private:
    QMap<QString, dde::network::WiredDevice*> m_wiredList;
    QMap<QString, dde::network::WirelessDevice*> m_wirelessList;
    QMap<dde::network::WirelessDevice*, QList<AccessPoint>> m_apMap;
    dde::network::WirelessDevice *m_currentWirelessDevice;
    QModelIndex m_hoverIndex;
};
}
}
#endif // NETWORKLISTMODEL_H
