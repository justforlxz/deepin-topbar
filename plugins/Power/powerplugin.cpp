#include "powerplugin.h"


PowerPlugin::PowerPlugin(QObject *parent) : QObject(parent)
{
    m_centralWidget = new Plugins::Power::PowerWidget;
}

PowerPlugin::~PowerPlugin()
{
    m_centralWidget->deleteLater();
}

const QString PowerPlugin::pluginName() const
{
    return QString("power");
}

void PowerPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, QString());
}

int PowerPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *PowerPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *PowerPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget->popup();
}

const QString PowerPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("dde-power");
}
