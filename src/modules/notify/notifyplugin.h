#ifndef NOTIFYPLUGIN_H
#define NOTIFYPLUGIN_H

#include "interfaces/pluginsiteminterface.h"

#include <QObject>
#include <QLabel>

class NotifyWidget;

namespace dtb {
namespace notify {

class NotifyPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    NotifyPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;
    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    NotifyWidget *m_notify;
    QLabel *m_notifyBtn;
};
}
}

#endif // NOTIFYPLUGIN_H
