#include "mainpanel.h"

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnect();
}

void MainPanel::initUI()
{
    setAttribute(Qt::WA_TranslucentBackground);

    m_mainLayout = new QHBoxLayout;
    m_itemController = PluginsItemController::instance(this);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(3);
    m_mainLayout->setContentsMargins(5, 0, 5, 0);
    setLayout(m_mainLayout);
}

void MainPanel::initConnect()
{
    connect(m_itemController, &PluginsItemController::itemInserted, this, &MainPanel::itemInserted, Qt::DirectConnection);
    connect(m_itemController, &PluginsItemController::itemRemoved, this, &MainPanel::itemRemoved, Qt::DirectConnection);
    connect(m_itemController, &PluginsItemController::itemMoved, this, &MainPanel::itemMoved, Qt::DirectConnection);
}

void MainPanel::itemInserted(const int index, Item *item)
{
    item->setVisible(true);
    item->setParent(this);

    // here can connect some func
    m_mainLayout->insertWidget(index, item);
}

void MainPanel::itemRemoved(Item *item)
{
    m_mainLayout->removeWidget(item);
}

void MainPanel::itemMoved(Item *item, const QPoint &point)
{
    item->setVisible(true);
    item->setParent(this);

    item->move(point);
}

void MainPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}
