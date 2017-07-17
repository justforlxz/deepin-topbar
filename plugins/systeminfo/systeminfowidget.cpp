#include "systeminfowidget.h"
#include <QHBoxLayout>

SystemInfoWidget::SystemInfoWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(70, 25);

    QLabel *up   = new QLabel("↑  ");
    QLabel *down = new QLabel("↓  ");

    m_rxPackets = new QLabel("100KB/s");
    m_rxPackets->setFixedHeight(10);

    m_txPackets = new QLabel("49KB/s");
    m_txPackets->setFixedHeight(10);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->setMargin(0);
    upLayout->setSpacing(0);
    upLayout->addWidget(up, 0, Qt::AlignLeft);
    upLayout->addWidget(m_txPackets, 0, Qt::AlignRight);

    QHBoxLayout *downLayout = new QHBoxLayout;
    downLayout->setMargin(0);
    downLayout->setSpacing(0);
    downLayout->addWidget(down, 0, Qt::AlignHCenter | Qt::AlignLeft);
    downLayout->addWidget(m_rxPackets, 0, Qt::AlignHCenter | Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(1);

    layout->addLayout(downLayout);
    layout->addLayout(upLayout);

    setLayout(layout);

//    setStyleSheet("QLabel {"
//                  "color: black;"
//                  "background: transparent;"
//                  "}"
//                  "QLabel:hover {"
//                  "color: white;"
//                  "background: #1E90FF;"
//                  "}");

    setStyleSheet(":hover {"
                  "background: #1E90FF;"
                  "}"
                  "{"
                  ""
                  "}");
}

void SystemInfoWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

//    setStyleSheet("background: #1E90FF;"
//                  "QLabel {"
//                  "color: white;"
//                  "}");


}

void SystemInfoWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

//    setStyleSheet("background: transparent;"
//                  "QLabel {"
//                  "color: black;"
//                  "}");
}
