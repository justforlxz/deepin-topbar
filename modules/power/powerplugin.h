#ifndef POWERPLUGIN_H
#define POWERPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
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

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;

    void popupShow() override;
    void popupHide() override;

    QMenu* itemContextMenu(const QString &itemKey);
    void invokedMenuItem(QAction *action);

private:
    PluginProxyInterface *m_proxyInter;
    PowerWidget *m_centralWidget;
};
}
}

#endif // POWERPLUGIN_H
