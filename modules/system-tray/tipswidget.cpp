#include "tipswidget.h"
#include "traywidget.h"

TrayApplet::TrayApplet(QWidget *parent)
    : ContentModule(parent),
      m_mainLayout(new QHBoxLayout)
{
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    setLayout(m_mainLayout);
    setFixedHeight(26);
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

void TrayApplet::addWidget(TrayWidget *widget)
{
    widget->setVisible(true);
    m_mainLayout->addWidget(widget);
}

void TrayApplet::addWidgets(QList<TrayWidget *> widgets)
{
    for (TrayWidget *w : widgets) {
        w->setVisible(true);
        m_mainLayout->addWidget(w);
    }
}
