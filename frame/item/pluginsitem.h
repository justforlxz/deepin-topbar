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

    ItemType itemType() const Q_DECL_OVERRIDE;
    const QString name() const Q_DECL_OVERRIDE;
    void finished() Q_DECL_OVERRIDE;

private:
    QWidget *popupTips() Q_DECL_OVERRIDE;
    PluginsItemInterface *itemInter() Q_DECL_OVERRIDE;

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
