#include "systeminfowidget.h"
#include "systeminfothread.h"
#include <QHBoxLayout>
#include <QPainter>

SystemInfoWidget::SystemInfoWidget(QWidget *parent) : QWidget(parent)
{
    setObjectName("SystemInfoWidget");
    setFixedSize(80, 25);

    m_enter = false;

    m_speedSort = new FontLabel;
    m_speedSort->setIcon(QChar(0xE8CB), 16);

    m_tx = new QLabel;
    m_tx->setFixedHeight(11);

    QFont font;
    font.setPixelSize(11);
    m_tx->setFont(font);

    m_rx = new QLabel;
    m_rx->setFixedHeight(12);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->setMargin(0);
    upLayout->setSpacing(0);
    upLayout->addWidget(m_tx, 0, Qt::AlignHCenter | Qt::AlignRight);

    QHBoxLayout *downLayout = new QHBoxLayout;
    downLayout->setMargin(0);
    downLayout->setSpacing(0);
    downLayout->addWidget(m_rx, 0, Qt::AlignHCenter | Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(1);

    layout->addLayout(upLayout);
    layout->addLayout(downLayout);

    QHBoxLayout *mainlayout = new QHBoxLayout;
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);

    mainlayout->addWidget(m_speedSort, 0, Qt::AlignHCenter | Qt::AlignLeft);
    mainlayout->addLayout(layout);


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
