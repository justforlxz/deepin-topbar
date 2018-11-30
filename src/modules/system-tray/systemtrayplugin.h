#ifndef SYSTEMTRAYPLUGIN_H
#define SYSTEMTRAYPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "tipswidget.h"
#include "dbus/dbustraymanager.h"
#include "xwindowtraywidget.h"

#include <QSettings>
#include <QLabel>

class StatusNotifierWatcher;

namespace dtb {
namespace systemtray {

class SystemTrayPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    explicit SystemTrayPlugin(QObject *parent = 0);

    const QString pluginName() const;
    void init(PluginProxyInterface *proxyInter);

    QWidget *itemWidget(const QString &itemKey);

    bool itemAllowContainer(const QString &itemKey);
    bool itemIsInContainer(const QString &itemKey);
    int itemSortKey(const QString &itemKey);
    void setItemIsInContainer(const QString &itemKey, const bool container);

    void setDefaultColor(PluginProxyInterface::DefaultColor color);

private:
    void updateTipsContent();
    const QString getWindowClass(quint32 winId);

private slots:
    void trayListChanged();
    void trayAdded(const QString &itemKey);
    void trayRemoved(const QString &itemKey);
    void trayChanged(quint32 winId);
//    void switchToMode(const Dock::DisplayMode mode);
    void sniItemsChanged();
    void sniItemIconChanged();

private:
    DBusTrayManager *m_trayInter;
    QMap<QString, AbstractTrayWidget *> m_trayList;

    TrayApplet *m_trayApplet;
    QLabel *m_tipsLabel;
    StatusNotifierWatcher *m_sniWatcher;
    QSettings *m_containerSettings;
};
}
}

#endif // SYSTEMTRAYPLUGIN_H
