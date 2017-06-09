#include "topbar.h"
#include <QLabel>
#include <QIcon>


#include "timewidget.h"

TopBar::TopBar(QWidget *parent) :
    QFrame(parent),
    m_mainLayout(new QHBoxLayout)
{
    QLabel *systemIcon = new QLabel;
    systemIcon->setPixmap(QIcon::fromTheme("dde").pixmap(20, 20));
    QLabel *systemName = new QLabel("Deepin 15.4.1");
    m_mainLayout->addSpacing(5);
    m_mainLayout->addWidget(systemIcon);
    m_mainLayout->addSpacing(2);
    m_mainLayout->addWidget(systemName);
    m_mainLayout->addStretch();

    TimeWidget *timeWidget = new TimeWidget;
    m_mainLayout->addWidget(timeWidget, 5, Qt::AlignRight);

    m_mainLayout->addSpacing(5);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);
}
