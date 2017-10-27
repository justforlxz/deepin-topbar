#include "wallpaperplugin.h"

using namespace dtb;
using namespace dtb::wallpaper;

WallpaperPlugin::WallpaperPlugin()
{
    m_Wallpaper = new WallpaperWidget;
    m_popupWidget = new WallpaperPopupWidget;
}

const QString WallpaperPlugin::pluginName() const
{
    return "wallpaper";
}

void WallpaperPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *WallpaperPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Wallpaper;
}

QMenu *WallpaperPlugin::itemContextMenu(const QString &itemKey)
{
    return m_Wallpaper->menu();
}
