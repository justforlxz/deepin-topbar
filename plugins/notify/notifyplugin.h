#ifndef NOTIFYPLUGIN_H
#define NOTIFYPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "notifypopupwidget.h"
#include "notifywidget.h"
#include <QObject>

class NotifyPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "notify.json")

public:
    NotifyPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    int itemSortKey(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QWidget *itemPopupApplet(const QString &itemKey) Q_DECL_OVERRIDE;

    const QString itemCommand(const QString &itemKey) Q_DECL_OVERRIDE;

    void popupShow() Q_DECL_OVERRIDE;
    void popupHide() Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    NotifyPopupWidget *m_popupWidget;
    NotifyWidget *m_notify;
};

#endif // NOTIFYPLUGIN_H
