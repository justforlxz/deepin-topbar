#include "pluginscontroller.h"
#include "pluginsitemcontroller.h"
#include "pluginloader.h"

PluginsController::PluginsController(PluginsItemController *itemControllerInter) :
    QObject(itemControllerInter),
    m_itemControllerInter(itemControllerInter)
{
    QTimer::singleShot(1, this, &PluginsController::startLoader);
}

void PluginsController::itemAdded(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    // check
    if (m_pluginList.contains(itemInter))
        if (m_pluginList[itemInter].contains(itemKey))
            return;

    PluginsItem *item = new PluginsItem(itemInter, itemKey);
    item->setVisible(false);

    m_pluginList[itemInter][itemKey] = item;

    emit pluginItemInserted(item);
}

void PluginsController::itemUpdate(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    PluginsItem *item = pluginItemAt(itemInter, itemKey);

    Q_ASSERT(item);

    item->update();

    emit pluginItemUpdated(item);
}

void PluginsController::itemRemoved(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    PluginsItem *item = pluginItemAt(itemInter, itemKey);

    if(!item)
        return;

    emit pluginItemRemoved(item);

    m_pluginList[itemInter].remove(itemKey);
    QTimer::singleShot(1, item, &PluginsItem::deleteLater);
}

void PluginsController::requestContextMenu(PluginsItemInterface * const itemInter, const QString &itemKey)
{
    PluginsItem *item = pluginItemAt(itemInter, itemKey);

    Q_ASSERT(item);


}

void PluginsController::requestHidePopup()
{
    for (QMap<QString, PluginsItem *> &map : m_pluginList.values()) {
        for (PluginsItem *item : map.values()) {
            item->hidePopup();
        }
    }
}

void PluginsController::move(const QString &itemKey, const float x, const float y)
{
    for (QMap<QString, PluginsItem *> &map : m_pluginList.values()) {
        for (PluginsItem *item : map.values()) {
            if (item->name() == itemKey) {
                emit itemMoved(item, QPoint(x, y));
            }
        }
    }
}

void PluginsController::startLoader()
{
    PluginLoader *loader = new PluginLoader(this);
    connect(loader, &PluginLoader::finished, this, &PluginsController::pluginItemFinished, Qt::QueuedConnection);
    connect(loader, &PluginLoader::finished, loader, &PluginLoader::deleteLater, Qt::QueuedConnection);
    connect(loader, &PluginLoader::pluginFounded, this, &PluginsController::loadPlugin, Qt::QueuedConnection);

    QTimer::singleShot(1, loader, [=]{
        loader->start(QThread::LowestPriority);
    });
}

void PluginsController::loadPlugin(const QString &pluginFile)
{
    qDebug() << "load plugin: " << pluginFile;

    QPluginLoader *pluginLoader = new QPluginLoader(pluginFile, this);
    PluginsItemInterface *interface = qobject_cast<PluginsItemInterface *>(pluginLoader->instance());
    if (!interface)
    {
        qWarning() << "load plugin failed!!!" << pluginLoader->errorString() << pluginFile;
        pluginLoader->unload();
        pluginLoader->deleteLater();
        return;
    }

    m_pluginList.insert(interface, QMap<QString, PluginsItem *>());
    qDebug() << "init plugin: " << interface->pluginName();
    interface->init(this);
    qDebug() << "init plugin finished: " << interface->pluginName();
}

PluginsItem * PluginsController::pluginItemAt(PluginsItemInterface * const itemInter, const QString &itemKey) const
{
    if (!m_pluginList.contains(itemInter))
        return nullptr;

    return m_pluginList[itemInter][itemKey];
}
