#ifndef NOTIFYPLUGIN_H
#define NOTIFYPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"

#include <QObject>

namespace dtb {
namespace notify {

class NotifyPopupWidget;
class NotifyWidget;

class NotifyPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    NotifyPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;


private:
    PluginProxyInterface *m_proxyInter;
    NotifyPopupWidget *m_popupWidget;
    NotifyWidget *m_notify;
};
}
}

#endif // NOTIFYPLUGIN_H
