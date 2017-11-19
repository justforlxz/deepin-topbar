#include "deviceitem.h"

#include <QPainter>

using namespace dtb;
using namespace dtb::network;

DeviceItem::DeviceItem(const QString &path)
    : ContentModule(nullptr)
    , m_devicePath(path)
    , m_networkManager(NetworkManager::instance(this))
    , m_menu(new QMenu)
{
    installEventFilter(this);

    connect(m_menu, &QMenu::aboutToHide, this, [=] {
        setStyleSheet("QLabel {color: rgb(67, 67, 62); background: transparent;} #ContentModule {background: transparent;}");
    });
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

bool DeviceItem::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this && event->type() == QEvent::MouseButtonPress) {
        setStyleSheet("QLabel {color: white; background: transparent;} #ContentModule {background: #1E90FF;}");
    }

    return ContentModule::eventFilter(watched, event);
}
