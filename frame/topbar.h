#ifndef TOPBAR_H
#define TOPBAR_H

#include "controller/pluginsitemcontroller.h"
#include "item/pluginsitem.h"
#include <QFrame>
#include <QHBoxLayout>

class TopBar : public QFrame
{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = 0);

private slots:
    void itemInserted(const int index, PluginsItem *item);
    void itemRemoved(PluginsItem *item);

private:
    QHBoxLayout *m_mainLayout;
    PluginsItemController *m_itemController;
};

#endif // TOPBAR_H
