#ifndef PLUGINPROXYINTERFACE_H
#define PLUGINPROXYINTERFACE_H

#include <QtCore>
#include <QJsonObject>

class PluginsItemInterface;
class PluginProxyInterface
{
public:
    ///
    /// \brief itemAdded
    /// add a new topbar item
    /// if itemkey of this plugin inter already exist, the new item
    /// will be ignored, so if you need to add multiple item, you need
    /// to ensure all itemKey is different.
    /// \param itemInter
    /// your plugin interface
    /// \param itemKey
    /// your item unique key
    ///
    virtual void itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey) = 0;
    ///
    /// \brief itemUpdate
    /// update(repaint) spec item
    /// \param itemInter
    /// \param itemKey
    ///
    virtual void itemUpdate(PluginsItemInterface * const itemInter, const QString &itemKey) = 0;
    ///
    /// \brief itemRemoved
    /// remove spec item, if spec item is not exist, topbar will to nothing.
    /// topbar will NOT delete your object, you should manage memory by your self.
    /// \param itemInter
    /// \param itemKey
    ///
    virtual void itemRemoved(PluginsItemInterface * const itemInter, const QString &itemKey) = 0;
    ///
    /// \brief requestContextMenu
    /// request show context menu
    ///
    virtual void requestContextMenu(PluginsItemInterface * const itemInter, const QString &itemKey) = 0;

    virtual void requestHidePopup() = 0;

    virtual void move(const QString &itemKey, const float x = 0, const float y = 0) = 0;

    virtual bool saveConfig(const QString &itemKey, const QJsonObject &json) { Q_UNUSED(itemKey); Q_UNUSED(json); return false;}

    virtual const QJsonObject loadConfig(const QString &itemKey) { Q_UNUSED(itemKey); return QJsonObject();}
};

#endif // PLUGINPROXYINTERFACE_H
