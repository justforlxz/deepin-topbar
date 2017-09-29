#ifndef SYSTEMTRAYPLUGIN_H
#define SYSTEMTRAYPLUGIN_H

#include "pluginsiteminterface.h"
#include "traywidget.h"
#include "tipswidget.h"
#include "dbus/dbustraymanager.h"

#include <QSettings>
#include <QLabel>

class SystemTrayPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "system-tray.json")

public:
    explicit SystemTrayPlugin(QObject *parent = 0);

    const QString pluginName() const;
    void init(PluginProxyInterface *proxyInter);

    QWidget *itemWidget(const QString &itemKey);
    QWidget *itemTipsWidget(const QString &itemKey);
    QWidget *itemPopupApplet(const QString &itemKey);

    bool itemAllowContainer(const QString &itemKey);
    bool itemIsInContainer(const QString &itemKey);
    int itemSortKey(const QString &itemKey);
    void setItemIsInContainer(const QString &itemKey, const bool container);

private:
    void updateTipsContent();
    const QString getWindowClass(quint32 winId);

private slots:
    void trayListChanged();
    void trayAdded(const quint32 winId);
    void trayRemoved(const quint32 winId);
    void trayChanged(const quint32 winId);
//    void switchToMode(const Dock::DisplayMode mode);

private:
    DBusTrayManager *m_trayInter;
    QMap<quint32, TrayWidget *> m_trayList;

    TrayApplet *m_trayApplet;
    QLabel *m_tipsLabel;

    QSettings *m_containerSettings;
};

#endif // SYSTEMTRAYPLUGIN_H
