#include "powerwidget.h"
#include "powerwidgetaction.h"
#include "widgets/fontlabel.h"
#include "widgets/dwidgetaction.h"
#include "frame/utils/global.h"

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
    setStyleSheet("QLabel {color: #d3d3d3; font-size: 11pt;}");
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

    m_powerInter = new PowerInter("com.deepin.daemon.Power", "/com/deepin/daemon/Power",
                                  QDBusConnection::sessionBus(), this);

    m_systemPowerInter =
        new SystemPowerInter("com.deepin.system.Power", "/com/deepin/system/Power",
                             QDBusConnection::systemBus(), this);
    m_systemPowerInter->setSync(true, true);
    m_powerInter->setSync(true, true);

    connect(m_systemPowerInter, &SystemPowerInter::BatteryStatusChanged, this,
            &PowerWidget::refreshTipsData);
    connect(m_systemPowerInter, &SystemPowerInter::BatteryTimeToEmptyChanged, this,
            &PowerWidget::refreshTipsData);
    connect(m_systemPowerInter, &SystemPowerInter::BatteryTimeToFullChanged, this,
            &PowerWidget::refreshTipsData);

    initMenu();

    updateBatteryIcon();

    connect(m_powerInter, &PowerInter::BatteryPercentageChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &PowerInter::BatteryStateChanged, this, &PowerWidget::updateBatteryIcon);
    connect(m_powerInter, &PowerInter::OnBatteryChanged, this, &PowerWidget::updateBatteryIcon);
}

void PowerWidget::updateBatteryIcon() {
    const BatteryPercentageInfo data = m_powerInter->batteryPercentage();

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

    refreshTipsData();
}

void PowerWidget::onActionHandle(const QString &action)
{
    if (action == "percentage") {
        return;
    }

    if (action == "lastTime") {
        emit requestEnableLastTime(!m_showLastTime);
        m_showLastTime = !m_showLastTime;
    }

    emit requestHidePopupWindow();

    if (action == "preference") {
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:power\"");
        return;
    }
}

void PowerWidget::initMenu()
{
    m_menu = new QMenu(this);

    m_sourceAction = new QAction(this);
    QAction* percentage = new QAction(tr("Show percentage"), this);
    QAction* lastTime = new QAction(tr("Show LastTime"), this);
    QAction* preference = new QAction(tr("Open Energy saver preferences"), this);

    m_sourceAction->setEnabled(false);

    percentage->setCheckable(true);
    percentage->setChecked(true);

    lastTime->setCheckable(true);

    m_menu->addAction(m_sourceAction);
    m_menu->addSeparator();
    m_menu->addAction(percentage);
    m_menu->addAction(lastTime);
    m_menu->addAction(preference);

    QSignalMapper *signalMapper = new QSignalMapper(this);

    connect(percentage, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    connect(preference, &QAction::triggered, signalMapper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));

    signalMapper->setMapping(percentage, "percentage");
    signalMapper->setMapping(lastTime, "lastTime");
    signalMapper->setMapping(preference, "preference");

    connect(signalMapper, static_cast<void (QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &PowerWidget::onActionHandle);
}

void PowerWidget::setEnableLastTime(const bool enable) {
    m_showLastTime = enable;
    updateBatteryIcon();
}

void PowerWidget::refreshTipsData() {
    const BatteryPercentageInfo data = m_powerInter->batteryPercentage();

    const uint    percentage   = qMin(100.0, qMax(0.0, data.value("Display")));
    const QString value        = QString("%1%").arg(std::round(percentage));
    const int     batteryState = m_powerInter->batteryState()["Display"];
    const bool    charging     = (batteryState == BatteryState::CHARGING ||
                           batteryState == BatteryState::FULLY_CHARGED);
    QString       tips;

    if (!charging) {
        qulonglong timeToEmpty = m_systemPowerInter->batteryTimeToEmpty();
        QDateTime  time        = QDateTime::fromTime_t(timeToEmpty).toUTC();
        uint       hour        = time.toString("hh").toUInt();
        uint       min         = time.toString("mm").toUInt();

        if (hour == 0) {
            tips = tr("%1 min remaining").arg(min);
        }
        else {
            tips = tr("%1 hr %2 min remaining").arg(hour).arg(min);
        }
    }
    else {
        qulonglong timeToFull = m_systemPowerInter->batteryTimeToFull();
        QDateTime  time       = QDateTime::fromTime_t(timeToFull).toUTC();
        uint       hour       = time.toString("hh").toUInt();
        uint       min        = time.toString("mm").toUInt();

        if (hour == 0) {
            tips = tr("%1 min until full").arg(min);
        }
        else {
            tips = tr("%1 hr %2 min until full").arg(hour).arg(min);
        }
    }

    m_battery->setText(
        QString("%1 %2").arg(charging ? tr("Charging") : tr("Capacity")).arg(value));

    if (!m_powerInter->batteryIsPresent().isEmpty()) {
        if (batteryState == BatteryState::FULLY_CHARGED || percentage == 100.) {
            m_sourceAction->setText(QString("%1: %2 (%3)")
                                        .arg(tr("Power source"))
                                        .arg(tr("Battery"))
                                        .arg(tr("Charged")));
        }
        else {
            m_sourceAction->setText(QString("%1: %2 (%3)")
                                        .arg(tr("Power source"))
                                        .arg(tr("Battery"))
                                        .arg(tips));
        }
    }
    else {
        m_sourceAction->setText(
            QString("%1: %2").arg(tr("Power source").arg(tr("Direct current"))));
    }
}
}
}
