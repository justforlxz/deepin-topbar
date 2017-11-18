#include "deviceitem.h"

using namespace dtb;
using namespace dtb::network;

DeviceItem::DeviceItem(const QString &path)
    : ContentModule(nullptr)
    , m_devicePath(path)
    , m_networkManager(NetworkManager::instance(this))
    , m_menu(new QMenu)
{
}

bool DeviceItem::enabled() const
{
    return m_networkManager->deviceEnabled(m_devicePath);
}

void DeviceItem::setEnabled(const bool enable)
{
    m_networkManager->setDeviceEnabled(m_devicePath, enable);
}

void DeviceItem::mouseReleaseEvent(QMouseEvent *event)
{
    ContentModule::mouseReleaseEvent(event);

    m_menu->exec(QPoint(mapToGlobal(rect().topLeft()).x(), height()));
}
