#include "mainpanel.h"
#include <QPainter>
#include <QPen>

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnect();
}

void MainPanel::initUI()
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
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
    m_mainLayout->removeWidget(item);
    item->setVisible(true);
    item->setParent(this);
    item->move(point);
}

void MainPanel::itemSort()
{

}

void MainPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPen pen(painter.pen());
    pen.setBrush(QColor(0, 0, 0, .3 * 255));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(QPoint(0, 27), QPoint(width(), 27));
}
