#include "powerpopupwidget.h"
#include "../widgets/switchitem.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSize>
#include <QScrollArea>

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

            resize(300, 100);

            QWidget *widget = new QWidget;
            QVBoxLayout *vlayout = new QVBoxLayout;
            widget->setLayout(vlayout);
            vlayout->addWidget(awakenDisplay, 0, Qt::AlignTop);
            vlayout->addWidget(awakenComputer, 0, Qt::AlignTop);
            vlayout->addStretch();

            QScrollArea *scrollarea = new QScrollArea;
            scrollarea->setWidget(widget);
            scrollarea->setObjectName("scrollarea");
            scrollarea->setWidgetResizable(true);
            scrollarea->setFocusPolicy(Qt::NoFocus);
            scrollarea->setFrameStyle(QFrame::NoFrame);
            scrollarea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            scrollarea->setContentsMargins(0, 0, 0, 0);
            scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            scrollarea->setStyleSheet("background-color:transparent;");

            m_mainLayout->addWidget(scrollarea, 0, Qt::AlignTop);

            QPushButton *button = new QPushButton(this);
            button->setText("高级设置");
            m_mainLayout->addWidget(button, 0, Qt::AlignBottom);

            connect(awakenDisplay, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenDisplayChanged);
            connect(awakenComputer, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenComputerChanged);

            QPropertyAnimation *showAdvancedSetting =new QPropertyAnimation(this, "size", this);
            showAdvancedSetting->setDuration(300);
            showAdvancedSetting->setStartValue(QSize(width(), 100));
            showAdvancedSetting->setEndValue(QSize(width(), 200));
            showAdvancedSetting->setEasingCurve(QEasingCurve::InOutCubic);

            QPropertyAnimation *hideAdvancedSetting =new QPropertyAnimation(this, "size", this);
            hideAdvancedSetting->setDuration(300);
            hideAdvancedSetting->setStartValue(QSize(width(), 200));
            hideAdvancedSetting->setEndValue(QSize(width(), 100));
            hideAdvancedSetting->setEasingCurve(QEasingCurve::InOutCubic);

            connect(button, &QPushButton::clicked, this, [=] {
                if (height() != 100) {
                    hideAdvancedSetting->start();
                } else {
                    showAdvancedSetting->start();
                }
            });
        }

        void PowerPopupWidget::onAwakenDisplayChanged(const bool state) {

        }

        void PowerPopupWidget::onAwakenComputerChanged(const bool state) {

        }
    }
}
