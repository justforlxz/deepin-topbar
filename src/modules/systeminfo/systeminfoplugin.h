#ifndef SYSTEMINFOPLUGIN_H
#define SYSTEMINFOPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "systeminfopopupwidget.h"
#include "systeminfowidget.h"
#include <QObject>

namespace dtb {
namespace systeminfo {
class SystemInfoModel;
class SysteminfoThread;
class SystemInfoPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    SystemInfoPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    SystemInfoPopupWidget *m_popupWidget;
    SystemInfoWidget *m_systeminfo;
    SystemInfoModel *m_systemModel;
    SysteminfoThread *m_systemWorker;
};
}
}

#endif // SYSTEMINFOPLUGIN_H
