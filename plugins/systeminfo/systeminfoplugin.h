#ifndef SYSTEMINFOPLUGIN_H
#define SYSTEMINFOPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "systeminfopopupwidget.h"
#include "systeminfowidget.h"
#include <QObject>

class SystemInfoPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "systeminfo.json")

public:
    SystemInfoPlugin();

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
    SystemInfoPopupWidget *m_popupWidget;
    SystemInfoWidget *m_systeminfo;
};

#endif // SYSTEMINFOPLUGIN_H
