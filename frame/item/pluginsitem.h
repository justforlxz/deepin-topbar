#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "../interfaces/pluginsiteminterface.h"
#include "item.h"
#include <QWidget>

namespace dtb {
class PluginsItem : public Item
{
    Q_OBJECT
public:
    explicit PluginsItem(PluginsItemInterface* const pluginInter, const QString &itemKey, QWidget *parent = 0);
    ~PluginsItem();

    const QString name() const Q_DECL_OVERRIDE;
    QMenu* contextMenu() const Q_DECL_OVERRIDE;
    void detachPluginWidget();

private:
    PluginsItemInterface *itemInter() Q_DECL_OVERRIDE;

signals:
    void requestRefershWindowVisible() const;

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void showContextMenu();

private:
    PluginsItemInterface * m_pluginInter;
    QWidget *m_centralWidget;
    QString m_itemKey;
    bool m_isPressed;
};
}

#endif // PLUGINSITEM_H
