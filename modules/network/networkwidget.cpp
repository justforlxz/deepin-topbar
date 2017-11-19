#include "networkwidget.h"
#include "item/deviceitem.h"

#include <QHBoxLayout>

using namespace dtb;
using namespace dtb::network;

NetworkWidget::NetworkWidget(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void NetworkWidget::addItem(DeviceItem *item)
{
    m_layout->addWidget(item);

    m_devices << item;
}

void NetworkWidget::remove(DeviceItem *item)
{
    m_layout->removeWidget(item);

    m_devices.removeOne(item);
}

void NetworkWidget::initUI()
{
    m_layout = new QHBoxLayout;

    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    setLayout(m_layout);
}
