#include "tipswidget.h"
#include "xwindowtraywidget.h"
#include <QDebug>

TrayApplet::TrayApplet(QWidget *parent)
    : ContentModule(parent),
      m_mainLayout(new QHBoxLayout)
{
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
}

void TrayApplet::clear()
{
    QLayoutItem *item = nullptr;
    while ((item = m_mainLayout->takeAt(0)) != nullptr)
    {
        if (item->widget())
            item->widget()->setParent(nullptr);
        delete item;
    }
}

void TrayApplet::addWidget(AbstractTrayWidget *widget)
{
    widget->setParent(this);
    widget->setVisible(true);
    widget->setFixedSize(TrayWidgetWidth, TrayWidgetHeight);
    m_mainLayout->addWidget(widget, 0, Qt::AlignCenter);
}

void TrayApplet::addWidgets(QList<AbstractTrayWidget *> widgets)
{
    for (AbstractTrayWidget *w : widgets)
        addWidget(w);
}

void TrayApplet::trayWidgetRemoved(AbstractTrayWidget *widget)
{
    m_mainLayout->removeWidget(widget);
}
