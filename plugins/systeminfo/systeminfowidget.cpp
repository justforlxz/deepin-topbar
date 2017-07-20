#include "systeminfowidget.h"
#include "systeminfothread.h"
#include <QHBoxLayout>
#include <QPainter>

SystemInfoWidget::SystemInfoWidget(QWidget *parent) : QWidget(parent)
{
    setObjectName("SystemInfoWidget");
    setFixedSize(80, 26);

    setStyleSheet("QLabel {"
                  "color: rgb(67, 67, 62);"
                  "font-size: 11px;"
                  "font-weight: 500;"
                  "}");

    m_enter = false;

    m_tx = new QLabel;
    m_tx->setFixedHeight(12);

    m_rx = new QLabel;
    m_rx->setFixedHeight(12);

    FontLabel *up = new FontLabel;
    up->setIcon(QChar(0xE935), 12);

    QHBoxLayout *uploadlayout = new QHBoxLayout;
    uploadlayout->setMargin(0);
    uploadlayout->setSpacing(0);
    uploadlayout->addWidget(up, 0, Qt::AlignVCenter | Qt::AlignLeft);
    uploadlayout->addWidget(m_tx, 0, Qt::AlignVCenter | Qt::AlignRight);

    FontLabel *down = new FontLabel;
    down->setIcon(QChar(0xE936), 12);

    QHBoxLayout *downlayout = new QHBoxLayout;
    downlayout->setMargin(0);
    downlayout->setSpacing(0);
    downlayout->addWidget(down, 0, Qt::AlignVCenter | Qt::AlignLeft);
    downlayout->addWidget(m_rx, 0, Qt::AlignVCenter | Qt::AlignRight);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout->setMargin(0);
    mainlayout->setSpacing(2);
    mainlayout->setContentsMargins(3, 0, 3, 0);
    mainlayout->addLayout(uploadlayout);
    mainlayout->addLayout(downlayout);

    setLayout(mainlayout);

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
                  "font-size: 11px;"
                  "font-weight: 500;"
                  "}");

    update();
}

void SystemInfoWidget::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);

    m_enter = false;

    setStyleSheet("QLabel {"
                  "color: rgb(67, 67, 62);"
                  "font-size: 11px;"
                  "font-weight: 500;"
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
