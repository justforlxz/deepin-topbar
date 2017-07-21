#ifndef PLUGINPROXYINTERFACE_H
#define PLUGINPROXYINTERFACE_H

#include <QtCore>

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

    virtual void move(const QString &itemKey, const float x, const float y) = 0;
};

#endif // PLUGINPROXYINTERFACE_H
