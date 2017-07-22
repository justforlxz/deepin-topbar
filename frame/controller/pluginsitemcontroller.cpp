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

const QMap<QString, Item *> PluginsItemController::itemList() const
{
    return m_itemList;
}

void PluginsItemController::itemSort()
{
    QMap<QString, Item *> list = m_itemList;

    for (Item * item : list.values())
        emit itemRemoved(item);

    int i = 0;

    emit itemInserted(i++, list.value("indicator"));
    list.remove("indicator");

    emit itemInserted(i++, list.value(""));
    list.remove("");

    emit itemInserted(i++, list.value("mediacontrol"));
    list.remove("mediacontrol");

    emit itemInserted(i++, list.value("systeminfo"));
    list.remove("systeminfo");

    emit itemInserted(i++, list.value("power"));
    list.remove("power");

    emit itemInserted(i++, list.value("datetime"));
    list.remove("datetime");

    emit itemInserted(i++, list.value("notify"));
    list.remove("notify");

    for (Item* item : list.values()) {
        emit itemInserted(2, item);
    }

    for (Item *item : m_itemList.values())
        item->finished();
}

PluginsItemController::PluginsItemController(QObject *parent)
    : QObject(parent)
    , m_pluginsInter(new PluginsController(this))
{
    StretchItem *item = new StretchItem;

    QTimer::singleShot(1000, this, [=]{
        pluginItemInserted(item);
    });

    connect(m_pluginsInter, &PluginsController::pluginItemFinished, this, &PluginsItemController::itemSort, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemInserted, this, &PluginsItemController::pluginItemInserted, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemRemoved, this, &PluginsItemController::pluginItemRemoved, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemMoved, this, &PluginsItemController::itemMoved, Qt::QueuedConnection);
    connect(m_pluginsInter, &PluginsController::pluginItemAdjust, this, &PluginsItemController::itemSort, Qt::QueuedConnection);
    // update pluginsItemController::itemUpdated
}

void PluginsItemController::pluginItemInserted(Item *item)
{
    if (m_itemList.keys().contains(item->name()))
        return;

    m_itemList.insert(item->name(), item);
}

void PluginsItemController::pluginItemRemoved(Item *item)
{
    m_itemList.remove(item->name());

    emit itemRemoved(item);
}
