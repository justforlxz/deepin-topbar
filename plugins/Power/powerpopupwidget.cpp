#include "powerpopupwidget.h"
#include "../widgets/switchitem.h"

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

            connect(awakenDisplay, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenDisplayChanged);
            connect(awakenComputer, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenComputerChanged);
        }

        void PowerPopupWidget::onAwakenDisplayChanged(const bool state) {

        }

        void PowerPopupWidget::onAwakenComputerChanged(const bool state) {

        }
    }
}
