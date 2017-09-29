#ifndef WallpaperPLUGIN_H
#define WallpaperPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "wallpaperpopupwidget.h"
#include "wallpaperwidget.h"
#include <QObject>

namespace dtb {
namespace wallpaper {

class WallpaperPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
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
}
}

#endif // WallpaperPLUGIN_H
