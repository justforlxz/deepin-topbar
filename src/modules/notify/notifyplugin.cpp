#include "notifyplugin.h"
#include "notifywidget.h"

#include <QApplication>

using namespace dtb;
using namespace dtb::notify;

NotifyPlugin::NotifyPlugin()
{
    m_notify = new NotifyWidget;
    m_notify->setFixedSize(360, 720 / qApp->devicePixelRatio());
}

const QString NotifyPlugin::pluginName() const
{
    return "Notify";
}

void NotifyPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *NotifyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return new QLabel("notify");
}

QWidget *NotifyPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_notify;
}

void NotifyPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{
    Q_UNUSED(color);
}
