#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "../interfaces/pluginsiteminterface.h"
#include "item.h"
#include "utils/event_monitor.h"
#include "dbus/dbusmenumanager.h"
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
    const QRect popupMarkGeometry() const;
    void showPopup() Q_DECL_OVERRIDE;
    void showPopupWindow(QWidget * const content) Q_DECL_OVERRIDE;
    void hidePopup() Q_DECL_OVERRIDE;
    QMenu* contextMenu() const Q_DECL_OVERRIDE;

private:
    QWidget *popupTips() Q_DECL_OVERRIDE;
    PluginsItemInterface *itemInter() Q_DECL_OVERRIDE;
    bool containsPoint(const QPoint &point) const;

signals:
    void requestRefershWindowVisible() const;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void showContextMenu();

private:
    PluginsItemInterface * m_pluginInter;
    QWidget *m_centralWidget;
    QString m_itemKey;
    EventMonitor *m_eventMonitor;
    DBusMenuManager *m_menuManagerInter;
};

#endif // PLUGINSITEM_H
