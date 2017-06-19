#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "../interfaces/pluginsiteminterface.h"
#include "dbus/dbusmenumanager.h"
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

signals:
    void requestRefershWindowVisible() const;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    PluginsItemInterface * const m_pluginInter;
    QWidget *m_centralWidget;
    QString m_itemKey;
    DBusMenuManager *m_menuManagerInter;
};

#endif // PLUGINSITEM_H
