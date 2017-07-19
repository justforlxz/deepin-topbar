#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "controller/pluginsitemcontroller.h"
#include "item/pluginsitem.h"
#include "item/item.h"
#include <QHBoxLayout>
#include <QWidget>

class MainPanel : public QWidget
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);
    void initUI();
    void initConnect();

private slots:
    void itemInserted(const int index, Item *item);
    void itemRemoved(Item *item);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QHBoxLayout *m_mainLayout;
    PluginsItemController *m_itemController;
};

#endif // MAINPANEL_H
