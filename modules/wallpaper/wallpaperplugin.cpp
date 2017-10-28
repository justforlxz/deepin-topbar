#include "wallpaperplugin.h"
#include "wallpaperworker.h"
#include "wallpapermodel.h"

using namespace dtb;
using namespace dtb::wallpaper;

WallpaperPlugin::WallpaperPlugin(QObject *parent)
    : QObject(parent)
    , m_proxyInter(nullptr)
    , m_wallpaper(new WallpaperWidget)
    , m_model(new WallpaperModel)
    , m_worker(new WallpaperWorker(m_model))
{
}

const QString WallpaperPlugin::pluginName() const
{
    return "wallpaper";
}

void WallpaperPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_wallpaper->setModel(m_model);

    m_model->moveToThread(qApp->thread());
    m_worker->moveToThread(qApp->thread());

    connect(m_wallpaper, &WallpaperWidget::requestSetWallpapers, m_worker, &WallpaperWorker::setWallpaperList);

    m_proxyInter->addItem(this, "");
}

QWidget *WallpaperPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_wallpaper;
}

QMenu *WallpaperPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_wallpaper->menu();
}
