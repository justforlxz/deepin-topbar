#ifndef WallpaperPLUGIN_H
#define WallpaperPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "wallpaperpopupwidget.h"
#include "wallpaperwidget.h"
#include <QObject>

class WallpaperPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "wallpaper.json")

public:
    WallpaperPlugin();

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
    WallpaperPopupWidget *m_popupWidget;
    WallpaperWidget *m_Wallpaper;
};

#endif // WallpaperPLUGIN_H
