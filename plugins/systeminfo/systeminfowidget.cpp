#include "systeminfowidget.h"
#include "systeminfothread.h"
#include <QHBoxLayout>
#include <QPainter>

SystemInfoWidget::SystemInfoWidget(QWidget *parent) : QWidget(parent)
{
    setObjectName("SystemInfoWidget");
    setFixedSize(70, 25);

    m_enter = false;

    QLabel *up   = new QLabel("↑  ");
    QLabel *down = new QLabel("↓  ");

    m_rx = new QLabel("100KB/s");
    m_rx->setFixedHeight(10);

    m_tx = new QLabel("49KB/s");
    m_tx->setFixedHeight(10);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->setMargin(0);
    upLayout->setSpacing(0);
    upLayout->addWidget(up, 0, Qt::AlignLeft);
    upLayout->addWidget(m_tx, 0, Qt::AlignRight);

    QHBoxLayout *downLayout = new QHBoxLayout;
    downLayout->setMargin(0);
    downLayout->setSpacing(0);
    downLayout->addWidget(down, 0, Qt::AlignHCenter | Qt::AlignLeft);
    downLayout->addWidget(m_rx, 0, Qt::AlignHCenter | Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(1);

    layout->addLayout(downLayout);
    layout->addLayout(upLayout);

    setLayout(layout);

    SysteminfoThread *systeminfoThread = new SysteminfoThread;

    connect(systeminfoThread, &SysteminfoThread::networkSpeedChanged, this, [=] (const quint64 tx, const quint64 rx) {
        m_tx->setText(converSpeed(tx));
        m_rx->setText(converSpeed(rx));
    });

    systeminfoThread->start();
}

void SystemInfoWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);

    m_enter = true;

    setStyleSheet("QLabel {"
                  "color: white;"
                  "}");

    update();
}

void SystemInfoWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    m_enter = false;

    setStyleSheet("QLabel {"
                  "color: black;"
                  "}");

    update();
}

void SystemInfoWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    if (m_enter) {
        painter.fillRect(rect(), QColor("#1E90FF"));
    }
}

const QString SystemInfoWidget::converSpeed(const int value)
{
    QString speed;

    for (;;) {
        if (value < 1024) {
            speed = QString::number(value) + "Bits/s";
            break;
        }
        if (value / 1024 < 1024) {
            speed = QString::number(value / 1024) + "KB/s";
            break;
        }
        if (value / 1024 / 1024 < 1024) {
            speed = QString::number(value / 1024 / 1024) + "MB/s";
            break;
        }
        if (value / 1024 / 1024 / 1024 < 1024) {
            speed = QString::number(value / 1024 / 1024 / 1024) + "GB/s";
            break;
        }
    }

    return speed;
}
