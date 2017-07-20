#include "wallpaperplugin.h"

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

    m_proxyInter->itemAdded(this, "wallpaper");

    connect(m_popupWidget, &WallpaperPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
}

int WallpaperPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *WallpaperPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Wallpaper;
}

QWidget *WallpaperPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

const QString WallpaperPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-wallpaper";
}

void WallpaperPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void WallpaperPlugin::popupHide()
{
    m_popupWidget->hideAni();
}
