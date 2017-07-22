#ifndef PLUGINSCONTROLLER_H
#define PLUGINSCONTROLLER_H

#include "../interfaces/pluginproxyinterface.h"
#include "item/pluginsitem.h"

#include <QObject>
#include <QDir>
#include <QStandardPaths>
#include <QFile>

class PluginsItemController;

class PluginsController : public QObject, PluginProxyInterface
{
    Q_OBJECT
public:
    explicit PluginsController(PluginsItemController *itemControllerInter = 0);

    // implements PluginProxyInterface
    void itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey);
    void itemUpdate(PluginsItemInterface * const itemInter, const QString &itemKey);
    void itemRemoved(PluginsItemInterface * const itemInter, const QString &itemKey);
    void requestContextMenu(PluginsItemInterface * const itemInter, const QString &itemKey);
    void requestHidePopup();
    void move(const QString &itemKey, const float x, const float y);
    bool saveConfig(const QString &itemKey, const QJsonObject &json);
    const QJsonObject loadConfig(const QString &itemKey);

signals:
    void pluginItemInserted(PluginsItem *pluginItem) const;
    void pluginItemRemoved(PluginsItem *pluginItem) const;
    void pluginItemUpdated(PluginsItem *pluginItem) const;
    void pluginItemFinished() const;
    void itemMoved(Item *item, const QPoint &point) const;

private slots:
    void startLoader();
    void loadPlugin(const QString &pluginFile);

private:
    PluginsItem *pluginItemAt(PluginsItemInterface * const itemInter, const QString &itemKey) const;

private:
    QMap<PluginsItemInterface *, QMap<QString, PluginsItem *>> m_pluginList;
    PluginsItemController *m_itemControllerInter;
};

#endif // PLUGINSCONTROLLER_H
