#include "systeminfoplugin.h"
#include "systeminfothread.h"
#include "systeminfomodel.h"

#include <QDBusInterface>

using namespace dtb;
using namespace dtb::systeminfo;

SystemInfoPlugin::SystemInfoPlugin()
{
    m_systeminfo = new SystemInfoWidget;
    m_systemModel = new SystemInfoModel;
    m_systemWorker = new SysteminfoThread(m_systemModel);
    m_systeminfo->setModel(m_systemModel);
}

const QString SystemInfoPlugin::pluginName() const
{
    return "SystemInfo";
}

void SystemInfoPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    QDBusInterface dbusInter("org.freedesktop.NetworkManager",
                             "/org/freedesktop/NetworkManager",
                             "org.freedesktop.NetworkManager",
                             QDBusConnection::systemBus(), this);

    if (dbusInter.isValid()) {
        m_proxyInter->addItem(this, "");
        m_systemWorker->start();
    }
}

QWidget *SystemInfoPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_systeminfo;
}

void SystemInfoPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}
