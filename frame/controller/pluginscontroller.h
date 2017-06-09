#ifndef PLUGINSCONTROLLER_H
#define PLUGINSCONTROLLER_H

#include "../interfaces/pluginproxyinterface.h"
#include "../item/pluginsitem.h"

#include <QObject>

class PluginsController : public QObject, PluginProxyInterface
{
    Q_OBJECT
public:
    explicit PluginsController(QObject *parent = 0);

    // implements PluginProxyInterface
    void itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey);
    void itemUpdate(PluginsItemInterface * const itemInter, const QString &itemKey);
    void itemRemoved(PluginsItemInterface * const itemInter, const QString &itemKey);
    void requestContextMenu(PluginsItemInterface * const itemInter, const QString &itemKey);

signals:
    void pluginItemInserted(PluginsItem *pluginItem) const;
    void pluginItemRemoved(PluginsItem *pluginItem) const;
    void pluginItemUpdated(PluginsItem *pluginItem) const;

public slots:
    void loadPlugin(const QString &pluginFile);

private:
    PluginsItem *pluginItemAt(PluginsItemInterface * const itemInter, const QString &itemKey) const;

private:
    QMap<PluginsItemInterface *, QMap<QString, PluginsItem *>> m_pluginList;
};

#endif // PLUGINSCONTROLLER_H
