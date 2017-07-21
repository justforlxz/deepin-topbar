#ifndef PLUGINSITEMINTERFACE_H
#define PLUGINSITEMINTERFACE_H

#include "pluginproxyinterface.h"

#include <QIcon>
#include <QtCore>

///
/// \brief The PluginsItemInterface class
/// the topbar plugins item interface, all topbar plugins should
/// inheirt this class and override all pure virtual function.
///
class PluginsItemInterface
{
public:
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
    virtual void init(PluginProxyInterface *proxyInter) = 0;
    ///
    /// \brief itemWidget
    /// your plugin item widget, each item should have a unique key.
    /// \param itemKey
    /// your widget' unqiue key.
    /// \return
    ///
    virtual QWidget *itemWidget(const QString &itemKey) = 0;

    ///
    /// \brief itemTipsWidget
    /// override this function if your item want to have a tips.
    /// the tips will shown when user hover your item.
    /// nullptr will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemTipsWidget(const QString &itemKey) {Q_UNUSED(itemKey); return nullptr;}
    ///
    /// \brief itemPopupApplet
    /// override this function if your item wants to have an popup applet.
    /// the popup applet will shown when user click your item.
    ///
    /// Tips:
    /// topbar should receive mouse press/release event to check user mouse operate,
    /// if your item filter mouse event, this function will not be called.
    /// so if you override mouse event and want to use popup applet, you
    /// should pass event to your parent use QWidget::someEvent(e);
    /// \param itemKey
    /// \return
    ///
    virtual QWidget *itemPopupApplet(const QString &itemKey) {Q_UNUSED(itemKey); return nullptr;}
    ///
    /// \brief itemCommand
    /// execute spec command when user clicked your item.
    /// ensure your command do not get user input.
    ///
    /// empty string will be ignored.
    /// \param itemKey
    /// \return
    ///
    virtual const QString itemCommand(const QString &itemKey) {Q_UNUSED(itemKey); return QString();}

    ///
    /// \brief itemSortKey
    /// tell topbar where your item wants to put on.
    ///
    /// this index is start from 1 and
    /// 0 for left side
    /// -1 for right side
    /// \param itemKey
    /// \return
    ///
    virtual int itemSortKey(const QString &itemKey) {Q_UNUSED(itemKey); return 1;}
    ///
    /// \brief setSortKey
    /// save your item new position
    /// sort key will be changed when plugins order
    /// changed(by user drag-drop)
    /// \param itemKey
    /// \param order
    ///
    virtual void setSortKey(const QString &itemKey, const int order) {Q_UNUSED(itemKey); Q_UNUSED(order);}

    ///
    /// \brief itemAllowContainer
    /// tell topbar is your item allow to move into container
    ///
    /// if your item placed into container, popup tips and popup
    /// applet will be disabled.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemAllowContainer(const QString &itemKey) {Q_UNUSED(itemKey); return false;}
    ///
    /// \brief itemIsInContainer
    /// tell topbar your item is in container, this function
    /// called at item init and if your item enable container.
    /// \param itemKey
    /// \return
    ///
    virtual bool itemIsInContainer(const QString &itemKey) {Q_UNUSED(itemKey); return false;}
    ///
    /// \brief setItemIsInContainer
    /// save your item new state.
    /// this function called when user drag out your item from
    /// container or user drop item into container(if your item
    /// allow drop into container).
    /// \param itemKey
    /// \param container
    ///
    virtual void setItemIsInContainer(const QString &itemKey, const bool container) {Q_UNUSED(itemKey); Q_UNUSED(container);}

    ///
    /// \brief refershIcon
    /// refersh item icon, its triggered when system icon theme changed.
    /// \param itemKey
    /// item key
    ///
    virtual void refershIcon(const QString &itemKey) { Q_UNUSED(itemKey); }

    virtual void popupShow() {}
    virtual void popupHide() {}

    virtual void finished() {}

protected:
    ///
    /// \brief m_proxyInter
    /// NEVER delete this object.
    ///
    PluginProxyInterface *m_proxyInter;
};

QT_BEGIN_NAMESPACE

#define ModuleInterface_iid "com.deepin.topbar.PluginsItemInterface"

Q_DECLARE_INTERFACE(PluginsItemInterface, ModuleInterface_iid)
QT_END_NAMESPACE

#endif // PLUGINSITEMINTERFACE_H
