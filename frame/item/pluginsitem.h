#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "../interfaces/pluginsiteminterface.h"
#include "item.h"
#include "utils/event_monitor.h"
#include "dbus/dbusmenumanager.h"
#include <QWidget>

namespace dtb {
class PluginsItem : public Item
{
    Q_OBJECT
public:
    explicit PluginsItem(PluginsItemInterface* const pluginInter, const QString &itemKey, QWidget *parent = 0);
    ~PluginsItem();

    const QString name() const Q_DECL_OVERRIDE;
    void finished() Q_DECL_OVERRIDE;
    const QRect popupMarkGeometry() const;
    QMenu* contextMenu() const Q_DECL_OVERRIDE;
    void detachPluginWidget();

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
}

#endif // PLUGINSITEM_H
