#include "systeminfowidget.h"
#include "systeminfomodel.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <DHiDPIHelper>

DWIDGET_USE_NAMESPACE

using namespace dtb;
using namespace dtb::systeminfo;

SystemInfoWidget::SystemInfoWidget(QWidget *parent)
    : ContentModule(parent)
{
    setObjectName("SystemInfoWidget");
    setStyleSheet("QLabel {color: #d3d3d3; font-size: 9px;}");
    setFixedWidth(180);

    m_tx = new QLabel;
    m_tx->setFixedHeight(10);
    m_tx->setText(converSpeed(0));

    m_rx = new QLabel;
    m_rx->setFixedHeight(10);
    m_rx->setText(converSpeed(0));

    m_cpu = new QLabel();
    m_cpu->setFixedHeight(20);
    m_cpu->setText("00%");
    m_cpu->setStyleSheet("QLabel {font-size: 16px;}");

    m_mem = new QLabel();
    m_mem->setFixedHeight(20);
    m_mem->setText("00%");
    m_mem->setStyleSheet("QLabel {font-size: 16px;}");



    QLabel *up = new QLabel;
    up->setPixmap(DHiDPIHelper::loadNxPixmap(":/right_top.svg").scaled(QSize(10, 10) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QHBoxLayout *uploadlayout = new QHBoxLayout;
    uploadlayout->setMargin(0);
    uploadlayout->setSpacing(0);
    uploadlayout->addWidget(up, 0, Qt::AlignVCenter | Qt::AlignLeft);
    uploadlayout->addWidget(m_tx, 0, Qt::AlignVCenter | Qt::AlignRight);

    QLabel *down = new QLabel;
    down->setPixmap(DHiDPIHelper::loadNxPixmap(":/left_down.svg").scaled(QSize(10, 10) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

    QHBoxLayout *downlayout = new QHBoxLayout;
    downlayout->setMargin(0);
    downlayout->setSpacing(0);
    downlayout->addWidget(down, 0, Qt::AlignVCenter | Qt::AlignLeft);
    downlayout->addWidget(m_rx, 0, Qt::AlignVCenter | Qt::AlignRight);

    QVBoxLayout *networklayout = new QVBoxLayout;
    networklayout->setMargin(0);
    networklayout->setSpacing(0);
    networklayout->addLayout(uploadlayout);
    networklayout->addLayout(downlayout);

    QLabel *cpuIcon = new QLabel();
    cpuIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/icon_cpu_dark.svg").scaled(QSize(24, 24) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QHBoxLayout *cpuLayout = new QHBoxLayout();
    cpuLayout->addWidget(cpuIcon, 0, Qt::AlignVCenter | Qt::AlignLeft);
    cpuLayout->addWidget(m_cpu, 0, Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *memIcon = new QLabel();
    memIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/icon_memory_dark.svg").scaled(QSize(24, 24) * devicePixelRatioF(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
    QHBoxLayout *memLayout = new QHBoxLayout();
    memLayout->addWidget(memIcon, 0, Qt::AlignVCenter | Qt::AlignLeft);
    memLayout->addWidget(m_mem, 0, Qt::AlignVCenter | Qt::AlignLeft);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
//    mainLayout->setContentsMargins(3, 2, 3, 2);
    mainLayout->addLayout(memLayout);
    mainLayout->addLayout(cpuLayout);
    mainLayout->addLayout(networklayout);
    setLayout(mainLayout);
}

void SystemInfoWidget::setModel(SystemInfoModel *model)
{
    m_model = model;

    connect(model, &SystemInfoModel::networkSpeedChanged, this, [=] (const quint64 tx, const quint64 rx) {
        m_tx->setText(converSpeed(tx));
        m_rx->setText(converSpeed(rx));
    });
    connect(model, &SystemInfoModel::cputimeChanged, this, [=](int cputime) {
        m_cpu->setText(formatPercent(cputime));
    });
    connect(model, &SystemInfoModel::memChanged, this, [=](int mem, int swap) {
        m_mem->setText(formatPercent(mem));
    });
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

const QString SystemInfoWidget::formatPercent(int percent) {
    if (percent < 10){
        return QString("0%1%").arg(percent);
    }
    return QString("%1%").arg(percent);
}
