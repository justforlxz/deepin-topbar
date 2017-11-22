#include "systeminfoplugin.h"
#include "systeminfothread.h"
#include "systeminfomodel.h"

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
    return "systeminfo";
}

void SystemInfoPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");

    m_systemWorker->start();
}

QWidget *SystemInfoPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_systeminfo;
}

void SystemInfoPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}
