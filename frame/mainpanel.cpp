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
    m_mainLayout->setSpacing(0);
    m_mainLayout->addStretch();
    setLayout(m_mainLayout);

    const QList<PluginsItem *> itemList = m_itemController->itemList();
    for (PluginsItem *item : itemList) {
        m_mainLayout->addWidget(item);
    }
}

void MainPanel::initConnect()
{
    connect(m_itemController, &PluginsItemController::itemInserted, this, &MainPanel::itemInserted, Qt::DirectConnection);
    connect(m_itemController, &PluginsItemController::itemRemoved, this, &MainPanel::itemRemoved, Qt::DirectConnection);
}

void MainPanel::itemInserted(const int index, PluginsItem *item)
{
    item->setVisible(true);
    item->setParent(this);

    // here can connect some func
    m_mainLayout->insertWidget(index, item);
}

void MainPanel::itemRemoved(PluginsItem *item)
{
    m_mainLayout->removeWidget(item);
}
