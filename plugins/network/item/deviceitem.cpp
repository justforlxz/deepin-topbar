#include "deviceitem.h"

DeviceItem::DeviceItem(const QString &path)
    : QWidget(nullptr),
      m_devicePath(path),

      m_networkManager(NetworkManager::instance(this))
{

}

QSize DeviceItem::sizeHint() const
{
    return QSize(26, 26);
}

const QString DeviceItem::itemCommand() const
{
    return QString();
}

const QString DeviceItem::itemContextMenu()
{
    QList<QVariant> items;
    items.reserve(2);

    QMap<QString, QVariant> enable;
    enable["itemId"] = "enable";
    if (!enabled())
        enable["itemText"] = tr("Enable network");
    else
        enable["itemText"] = tr("Disable network");
    enable["isActive"] = true;
    items.push_back(enable);

    QMap<QString, QVariant> settings;
    settings["itemId"] = "settings";
    settings["itemText"] = tr("Network settings");
    settings["isActive"] = true;
    items.push_back(settings);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    return QJsonDocument::fromVariant(menu).toJson();
}

QWidget *DeviceItem::itemPopup()
{
    return nullptr;
}

void DeviceItem::invokeMenuItem(const QString &menuId)
{
    if (menuId == "settings")
        QProcess::startDetached("dde-control-center", QStringList() << "network");
    else if (menuId == "enable")
        setEnabled(!enabled());
}

bool DeviceItem::enabled() const
{
    return m_networkManager->deviceEnabled(m_devicePath);
}

void DeviceItem::setEnabled(const bool enable)
{
    m_networkManager->setDeviceEnabled(m_devicePath, enable);
}

QWidget *DeviceItem::itemApplet()
{
    return nullptr;
}
