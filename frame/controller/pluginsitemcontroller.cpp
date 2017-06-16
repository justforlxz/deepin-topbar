#include "pluginsitemcontroller.h"
#include "item/stretchitem.h"
#include <QFrame>

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

const QList<Item *> PluginsItemController::itemList() const
{
    return m_itemList;
}

PluginsItemController::PluginsItemController(QObject *parent)
    : QObject(parent)
    , m_pluginsInter(new PluginsController(this))
{
    StretchItem *item = new StretchItem;

    QTimer::singleShot(1000, this, [=]{
        pluginItemInserted(item);
    });

    connect(m_pluginsInter, &PluginsController::pluginItemInserted, this, &PluginsItemController::pluginItemInserted, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemRemoved, this, &PluginsItemController::pluginItemRemoved, Qt::QueuedConnection);
    // update pluginsItemController::itemUpdated
}

void PluginsItemController::pluginItemInserted(Item *item)
{
    // here need record item position
    // I need to think about whether I need the type
    // Anyway, I need a list that I can keep

    switch (item->itemType()) {
    case Item::Indicator:
        emit itemInserted(0, item);
        break;
    case Item::DateTime:
        emit itemInserted(-1, item);
        break;
    case Item::Stretch:
        emit itemInserted(0, item);
        break;
    case Item::Plugin:
        emit itemInserted(m_itemList.count() - 1, item);
        break;
    default:
        emit itemInserted(m_itemList.count() - 1, item);
        break;
    }

    m_itemList.append(item);
}

void PluginsItemController::pluginItemRemoved(Item *item)
{
    m_itemList.removeOne(item);

    emit itemRemoved(item);
}
