#include "powerpopupwidget.h"
#include "../widgets/switchitem.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>

using namespace topbar::widgets;

namespace Plugins {
    namespace Power {
        PowerPopupWidget::PowerPopupWidget(QWidget *parent) : QWidget(parent) {
            m_mainLayout = new QVBoxLayout;
            m_mainLayout->setMargin(7);
            m_mainLayout->setSpacing(7);
            setLayout(m_mainLayout);

            SwitchItem *awakenDisplay = new SwitchItem;
            awakenDisplay->setCheck(false);
            awakenDisplay->setText("唤醒显示器时需要密码");

            SwitchItem *awakenComputer = new SwitchItem;
            awakenComputer->setCheck(false);
            awakenComputer->setText("唤醒计算机时需要密码");

            m_mainLayout->addWidget(awakenDisplay);
            m_mainLayout->addWidget(awakenComputer);
            m_mainLayout->addStretch();

            QPushButton *button = new QPushButton;
            m_mainLayout->addWidget(button);

            resize(300, 100);

            connect(awakenDisplay, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenDisplayChanged);
            connect(awakenComputer, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenComputerChanged);

            QPropertyAnimation *showAdvancedSetting =new QPropertyAnimation(this, "size", this);
            showAdvancedSetting->setDuration(300);
            showAdvancedSetting->setStartValue(QSize(width(), height()));
            showAdvancedSetting->setEndValue(QSize(width(), height() + 100));
            showAdvancedSetting->setEasingCurve(QEasingCurve::InOutCubic);

            QPropertyAnimation *hideAdvancedSetting =new QPropertyAnimation(this, "size", this);
            hideAdvancedSetting->setDuration(300);
            hideAdvancedSetting->setStartValue(QSize(width(), height() + 100));
            hideAdvancedSetting->setEndValue(QSize(width(), height() - 100));
            hideAdvancedSetting->setEasingCurve(QEasingCurve::InOutCubic);

            connect(button, &QPushButton::clicked, this, [=] {
                if (height() != 100)
                    hideAdvancedSetting->start();
                else
                    showAdvancedSetting->start();
            });
        }

        void PowerPopupWidget::onAwakenDisplayChanged(const bool state) {

        }

        void PowerPopupWidget::onAwakenComputerChanged(const bool state) {

        }
    }
}
