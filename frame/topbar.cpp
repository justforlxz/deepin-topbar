#include "topbar.h"
#include <QLabel>
#include <QIcon>

TopBar::TopBar(QWidget *parent) :
    QFrame(parent),
    m_mainLayout(new QHBoxLayout),
    m_itemController(PluginsItemController::instance(this))
{
    QLabel *systemIcon = new QLabel;
    systemIcon->setPixmap(QIcon::fromTheme("dde").pixmap(20, 20));
    QLabel *systemName = new QLabel("Deepin 15.4.1");
    m_mainLayout->addSpacing(5);
    m_mainLayout->addWidget(systemIcon);
    m_mainLayout->addSpacing(2);
    m_mainLayout->addWidget(systemName);
    m_mainLayout->addStretch();

    m_mainLayout->addSpacing(5);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);

    connect(m_itemController, &PluginsItemController::itemInserted, this, &TopBar::itemInserted, Qt::DirectConnection);
    connect(m_itemController, &PluginsItemController::itemRemoved, this, &TopBar::itemRemoved, Qt::DirectConnection);

    const QList<PluginsItem *> itemList = m_itemController->itemList();
    for (PluginsItem *item : itemList) {
        m_mainLayout->addWidget(item);
    }
}

void TopBar::itemInserted(const int index, PluginsItem *item)
{
    item->setVisible(true);
    item->setParent(this);

    // here can connect some func

    m_mainLayout->insertWidget(index, item);
}

void TopBar::itemRemoved(PluginsItem *item)
{
    m_mainLayout->removeWidget(item);
}
