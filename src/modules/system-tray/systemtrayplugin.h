#ifndef SYSTEMTRAYPLUGIN_H
#define SYSTEMTRAYPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "tipswidget.h"
#include "dbus/dbustraymanager.h"
#include "xwindowtraywidget.h"
#include "sni/statusnotifierwatcher.h"

#include <QSettings>
#include <QLabel>

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
    int itemSortKey(const QString &itemKey);

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
    org::kde::StatusNotifierWatcher *m_sniWatcher;
    QString m_sniHostService;
};
}
}

#endif // SYSTEMTRAYPLUGIN_H
