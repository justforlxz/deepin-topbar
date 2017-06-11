#include "pluginsitemcontroller.h"

PluginsItemController *PluginsItemController::INSTANCE = nullptr;

PluginsItemController *PluginsItemController::instance(QObject *parent)
{
    if (!INSTANCE)
        INSTANCE = new PluginsItemController(parent);

    return INSTANCE;
}

PluginsItemController::~PluginsItemController()
{

}

const QList<PluginsItem *> PluginsItemController::itemList() const
{
    return m_itemList;
}

PluginsItemController::PluginsItemController(QObject *parent)
    : QObject(parent)
    , m_pluginsInter(new PluginsController(this))
{

    connect(m_pluginsInter, &PluginsController::pluginItemInserted, this, &PluginsItemController::pluginItemInserted, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemRemoved, this, &PluginsItemController::pluginItemRemoved, Qt::QueuedConnection);
    // update pluginsItemController::itemUpdated
}

void PluginsItemController::pluginItemInserted(PluginsItem *item)
{
    // here need record item position
    // I need to think about whether I need the type
    // Anyway, I need a list that I can keep

    m_itemList.append(item);

    emit itemInserted(1, item);

}

void PluginsItemController::pluginItemRemoved(PluginsItem *item)
{
    m_itemList.removeOne(item);

    emit itemRemoved(item);
}
