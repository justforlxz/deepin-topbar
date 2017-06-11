#ifndef PLUGINSITEMCONTROLLER_H
#define PLUGINSITEMCONTROLLER_H

#include "pluginscontroller.h"
#include "item/pluginsitem.h"

#include <QObject>

class PluginsItemController : public QObject
{
    Q_OBJECT
public:
    static PluginsItemController *instance(QObject *parent);
    ~PluginsItemController();

    const QList<PluginsItem *> itemList() const;

signals:
    void itemInserted(const int index, PluginsItem *item) const;
    void itemRemoved(PluginsItem *item) const;

private:
    explicit PluginsItemController(QObject *parent = nullptr);
    void pluginItemInserted(PluginsItem *item);
    void pluginItemRemoved(PluginsItem *item);

private:
    QList<PluginsItem *> m_itemList;
    PluginsController *m_pluginsInter;

    static PluginsItemController *INSTANCE;
};

#endif // PLUGINSITEMCONTROLLER_H
