#ifndef MEDIACONTROLPLUGIN_H
#define MEDIACONTROLPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "View/mediacontrolwidget.h"
#include <QObject>
#include <QLabel>

class MediaControlPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "mediacontrol.json")

public:
    MediaControlPlugin(QObject *parent = 0);
    ~MediaControlPlugin();

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;
    const QString itemContextMenu(const QString &itemKey) override;

    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    MediaControlWidget *m_centralWidget;
    QLabel *m_tip;
};

#endif // MEDIACONTROLPLUGIN_H
