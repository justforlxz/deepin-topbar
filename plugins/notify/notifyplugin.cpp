#include "notifyplugin.h"


NotifyPlugin::NotifyPlugin()
{
}

const QString NotifyPlugin::pluginName() const
{
    return "notify";
}

void NotifyPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
}

int NotifyPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *NotifyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return nullptr;
}

QWidget *NotifyPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return nullptr;
}

const QString NotifyPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "dde-notify";
}
