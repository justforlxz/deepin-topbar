#ifndef POWERPLUGIN_H
#define POWERPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "powerwidget.h"
#include <QObject>

namespace dtb {
namespace power {

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

private:
    PluginProxyInterface *m_proxyInter;
    PowerWidget *m_centralWidget;
};
}
}

#endif // POWERPLUGIN_H
