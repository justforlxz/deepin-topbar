#include "powerwidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>

namespace Plugins {
    namespace Power {
        PowerWidget::PowerWidget(QWidget *parent) : QWidget(parent) {
            m_popup = new PowerPopupWidget;

            m_batteryIcon = new QLabel;
            m_battery = new QLabel;

            QHBoxLayout *layout = new QHBoxLayout;
            layout->setMargin(0);
            layout->setSpacing(5);
            layout->addWidget(m_batteryIcon, 0, Qt::AlignVCenter);
            layout->addWidget(m_battery, 0, Qt::AlignVCenter);

            setLayout(layout);

            setStyleSheet("QLabel {"
                          "font: 14px;"
                          "}");

            m_powerInter = new DBusPower(this);

            updateBatteryIcon();

            connect(m_powerInter, &DBusPower::BatteryPercentageChanged, this, &PowerWidget::updateBatteryIcon);
            connect(m_powerInter, &DBusPower::BatteryStateChanged, this, &PowerWidget::updateBatteryIcon);
            connect(m_powerInter, &DBusPower::OnBatteryChanged, this, &PowerWidget::updateBatteryIcon);

            connect(m_popup, &PowerPopupWidget::requestHidePopup, this, &PowerWidget::requestHidePopup);
        }

        QWidget *PowerWidget::popup() {
            return m_popup;
        }

        void PowerWidget::updateBatteryIcon() {
            const BatteryPercentageMap data = m_powerInter->batteryPercentage();
            const uint value = qMin(100.0, qMax(0.0, data.value("Display")));
            const int percentage = std::round(value);
            const bool plugged = !m_powerInter->onBattery();

            QString percentageStr;
            if (percentage < 10 && percentage >= 0) {
                percentageStr = "000";
            } else if (percentage < 30) {
                percentageStr = "020";
            } else if (percentage < 50) {
                percentageStr = "040";
            } else if (percentage < 70) {
                percentageStr = "060";
            } else if (percentage < 90) {
                percentageStr = "080";
            } else if (percentage <= 100){
                percentageStr = "100";
            } else {
                percentageStr = "000";
            }

            QString iconStr;

            if (plugged) {
                iconStr = "battery-charged-symbolic";
            } else {
                iconStr = QString("battery-%1-symbolic").arg(percentageStr);
            }
            m_battery->setText(percentageStr + "%");
            m_batteryIcon->setPixmap(QIcon::fromTheme(iconStr).pixmap(16, 16));
        }
    }
}
