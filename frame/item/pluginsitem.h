#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "../interfaces/pluginsiteminterface.h"
#include "item.h"
#include <QWidget>

class PluginsItem : public Item
{
    Q_OBJECT
public:
    explicit PluginsItem(PluginsItemInterface* const pluginInter, const QString &itemKey, QWidget *parent = 0);
    ~PluginsItem();

    ItemType itemType() const;
    const QString name() const;

private:
    QWidget *popupTips();
    PluginsItemInterface *itemInter();

signals:
    void requestRefershWindowVisible() const;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    PluginsItemInterface * m_pluginInter;
    QWidget *m_centralWidget;
    QString m_itemKey;
};

#endif // PLUGINSITEM_H
