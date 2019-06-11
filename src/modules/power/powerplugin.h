#ifndef POWERPLUGIN_H
#define POWERPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "powerwidget.h"
#include <QObject>
#include <com_deepin_system_systempower.h>

using SystemPowerInter = com::deepin::system::Power;

namespace dtb {
namespace power {
class PowerPopupWidget;
class PowerModel;
class PowerPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    PowerPlugin(QObject *parent = 0);
    ~PowerPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private slots:
    void onbatteryStatusChanged(uint state);

private:
    PluginProxyInterface *m_proxyInter;
    PowerWidget *m_centralWidget;
    PowerPopupWidget* m_popupWidget;
    PowerModel* m_model;
    SystemPowerInter *m_systemPowerInter;
};
}
}

#endif // POWERPLUGIN_H
