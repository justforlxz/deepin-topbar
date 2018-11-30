#ifndef PLUGINSITEMINTERFACE_H
#define PLUGINSITEMINTERFACE_H

#include "pluginproxyinterface.h"

#include <QIcon>
#include <QtCore>
#include <QMenu>

///
/// \brief The PluginsItemInterface class
/// the topbar plugins item interface, all topbar plugins should
/// inheirt this class and override all pure virtual function.
///

namespace dtb {

class PluginsItemInterface
{
public:

    PluginsItemInterface() {}

    ///
    /// \brief ~PluginsItemInterface
    /// DON'T try to delete m_proxyInter.
    ///
    virtual ~PluginsItemInterface() {}

    ///
    /// \brief pluginName
    /// tell topbar the unique plugin id
    /// \return
    ///
    virtual const QString pluginName() const = 0;
    ///
    /// \brief init
    /// init your plugins, you need to save proxyInter to m_proxyInter
    /// member variable. but you shouldn't free this pointer.
    /// \param proxyInter
    /// DON'T try to delete this pointer.
    ///
    virtual void init(PluginProxyInterface *proxyInter) { m_proxyInter = proxyInter;}
    ///
    /// \brief itemWidget
    /// your plugin item widget, each item should have a unique key.
    /// \param itemKey
    /// your widget' unqiue key.
    /// \return
    ///
    virtual QWidget *itemWidget(const QString &itemKey) = 0;

    virtual QWidget* itemContextMenu(const QString &itemKey) { Q_UNUSED(itemKey); return nullptr;}

    virtual void setDefaultColor(PluginProxyInterface::DefaultColor) {}

protected:
    ///
    /// \brief m_proxyInter
    /// NEVER delete this object.
    ///
    PluginProxyInterface *m_proxyInter;
};
}

#endif // PLUGINSITEMINTERFACE_H
