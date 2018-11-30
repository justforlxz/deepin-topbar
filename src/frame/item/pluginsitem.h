#ifndef PLUGINSITEM_H
#define PLUGINSITEM_H

#include "interfaces/pluginsiteminterface.h"
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
    QWidget* contextMenu() const Q_DECL_OVERRIDE;
    void detachPluginWidget();

private:
    PluginsItemInterface *itemInter() Q_DECL_OVERRIDE;

signals:
    void requestRefershWindowVisible() const;

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

protected slots:
    void showTips();

private:
    PluginsItemInterface * m_pluginInter;
    QWidget *m_centralWidget;
    QString m_itemKey;
};
}

#endif // PLUGINSITEM_H
