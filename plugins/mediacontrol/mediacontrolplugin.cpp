#include "mediacontrolplugin.h"

MediaControlPlugin::MediaControlPlugin(QObject *parent) : QObject(parent)
{
    m_centralWidget = new MediaControlWidget;
    m_tip = new QLabel;
}

MediaControlPlugin::~MediaControlPlugin()
{

}

const QString MediaControlPlugin::pluginName() const
{
    return QString("mediacontrol");
}

void MediaControlPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, QString());
}

int MediaControlPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *MediaControlPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *MediaControlPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_tip;
}

const QString MediaControlPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("dde-mediacontrol");
}

const QString MediaControlPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString();
}

void MediaControlPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)
    Q_UNUSED(menuId)
}
