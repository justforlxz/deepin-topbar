#include "powerwidget.h"
#include "dbuspower.h"
#include "powerwidgetaction.h"
#include "fontlabel.h"
#include "dwidgetaction.h"
#include "utils/global.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QSignalMapper>
#include <DHiDPIHelper>

DWIDGET_USE_NAMESPACE

using namespace dtb::widgets;

namespace dtb {
namespace power {
PowerWidget::PowerWidget(QWidget *parent)
    : ContentModule(parent)
{
    setStyleSheet("QLabel {color: #d3d3d3; font-size: 16px; font-weight: 550; }");
    m_powerActionWidget = new PowerWidgetAction;

    m_batteryIcon = new QLabel;
    m_battery = new QLabel;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(3);
    layout->setContentsMargins(3, 0, 3, 0);
    layout->addWidget(m_batteryIcon, 0, Qt::AlignVCenter);
    layout->addSpacing(5);
    layout->addWidget(m_battery, 0, Qt::AlignVCenter);

    setLayout(layout);

    m_powerInter = new DBusPower(this);

    initMenu();

    updateBatteryIcon();

    connect(m_powerInter, &DBusPower::BatteryPercentageChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &DBusPower::BatteryStateChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &DBusPower::OnBatteryChanged, this, &PowerWidget::updateBatteryIcon);
}

void PowerWidget::updateBatteryIcon() {
    const BatteryPercentageMap data = m_powerInter->batteryPercentage();

    m_sourceAction->setText(tr("Power source:") + (m_powerInter->onBattery() ? tr("Battery") : tr("Direct current")));

    if (data.isEmpty()) {
        m_battery->hide();
        m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/full-battery.svg"));
        return;
    }

    m_battery->show();

    const uint value = qMin(100.0, qMax(0.0, data.value("Display")));
    const int percentage = std::round(value);
    const bool plugged = !m_powerInter->onBattery();

    if (plugged) {
        m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/full-battery.svg"));
    }
    else {
        if (percentage >= 90) {
            m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/full-battery.svg"));
        }
        else if (percentage >= 80) {
            m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/battery-charging-status.svg"));
        }
        else if (percentage >= 50) {
            m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/half-battery.svg"));
        }
        else if (percentage >= 30) {
            m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/low-battery.svg"));
        }
        else {
            m_batteryIcon->setPixmap(DHiDPIHelper::loadNxPixmap(":/Icons/battery.svg"));
        }
    }

    m_battery->setText(QString::number(percentage) + "%");
}

void PowerWidget::onActionHandle(const QString &action)
{
    if (action == "percentage") {

        return;
    }

    if (action == "preference") {
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:power\"");
        return;
    }
}

void PowerWidget::initMenu()
{
    m_menu = new QMenu;

    m_sourceAction = new QAction(this);
    QAction *percentage = new QAction(tr("Show percentage"), this);
    QAction *preference = new QAction(tr("Open Energy saver preferences"), this);

    m_sourceAction->setEnabled(false);

    percentage->setCheckable(true);
    percentage->setChecked(true);

    m_menu->addAction(m_sourceAction);
    m_menu->addSeparator();
    m_menu->addAction(percentage);
    m_menu->addAction(preference);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(percentage, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(preference, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    signalMapper->setMapping(percentage, "percentage");
    signalMapper->setMapping(preference, "preference");

    connect(signalMapper, static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &PowerWidget::onActionHandle);
}
}
}
