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
    setLayout(m_mainLayout);

    const QList<Item *> itemList = m_itemController->itemList();
    for (Item *item : itemList) {
        switch (item->itemType()) {
        case Item::Indicator:
            m_mainLayout->insertWidget(0, item);
            break;
        case Item::DateTime:
            m_mainLayout->insertWidget(2, item);
            break;
        case Item::Stretch:
            m_mainLayout->insertWidget(1, item);
            break;
        case Item::Plugin:
            m_mainLayout->insertWidget(2, item);
            break;
        default:
            break;
        }
    }
}

void MainPanel::initConnect()
{
    connect(m_itemController, &PluginsItemController::itemInserted, this, &MainPanel::itemInserted, Qt::DirectConnection);
    connect(m_itemController, &PluginsItemController::itemRemoved, this, &MainPanel::itemRemoved, Qt::DirectConnection);
}

void MainPanel::itemInserted(const int index, Item *item)
{
    item->setVisible(true);
    item->setParent(this);

    qDebug() << index;

    // here can connect some func
    m_mainLayout->insertWidget(index, item);
}

void MainPanel::itemRemoved(Item *item)
{
    m_mainLayout->removeWidget(item);
}
