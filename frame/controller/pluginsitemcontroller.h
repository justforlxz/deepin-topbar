#ifndef PLUGINSITEMCONTROLLER_H
#define PLUGINSITEMCONTROLLER_H

#include "pluginscontroller.h"
#include "item/item.h"

#include <QObject>

class PluginsItemController : public QObject
{
    Q_OBJECT
public:
    static PluginsItemController *instance(QObject *parent);
    ~PluginsItemController();

    const QMap<QString, Item *> itemList() const;

signals:
    void itemInserted(const int index, Item *item) const;
    void itemRemoved(Item *item) const;
    void itemMoved(Item *item, const QPoint &point) const;

private slots:
    void itemSort();

private:
    explicit PluginsItemController(QObject *parent = nullptr);
    void pluginItemInserted(Item *item);
    void pluginItemRemoved(Item *item);

private:
    QMap<QString, Item *> m_itemList;
    PluginsController *m_pluginsInter;

    static PluginsItemController *INSTANCE;
};

#endif // PLUGINSITEMCONTROLLER_H
