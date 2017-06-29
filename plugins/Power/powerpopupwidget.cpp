#include "powerpopupwidget.h"
#include "../widgets/switchitem.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSize>
#include <QScrollArea>
#include <QRadioButton>
#include <QFile>

using namespace topbar::widgets;

namespace Plugins {
    namespace Power {
        PowerPopupWidget::PowerPopupWidget(QWidget *parent) : QWidget(parent) {
            m_mainLayout = new QVBoxLayout;
            m_mainLayout->setMargin(0);
            m_mainLayout->setSpacing(7);
            setLayout(m_mainLayout);

            QVBoxLayout *baseLayout = new QVBoxLayout;
            QWidget *base = new QWidget;
            base->setLayout(baseLayout);

            QFile file("/usr/bin/cpufreq-info");
            if (file.exists())
                baseLayout->addWidget(createPowerStateGrp());

            m_mainLayout->addWidget(base);

            SwitchItem *awakenDisplay = new SwitchItem;
            awakenDisplay->setCheck(false);
            awakenDisplay->setText(tr("Password required to wake up the monitor"));

            SwitchItem *awakenComputer = new SwitchItem;
            awakenComputer->setCheck(false);
            awakenComputer->setText(tr("Password required to wake up the computer"));

            SwitchItem *powerPercent = new SwitchItem;
            powerPercent->setText(tr("Enable Percent"));

            resize(300, 100);

            QWidget *widget = new QWidget;
            widget->setFixedWidth(300);

            QVBoxLayout *vlayout = new QVBoxLayout;
            widget->setLayout(vlayout);
            vlayout->setContentsMargins(0, 5, 0, 5);
            vlayout->addWidget(awakenDisplay, 0, Qt::AlignTop);
            vlayout->addWidget(awakenComputer, 0, Qt::AlignTop);
            vlayout->addWidget(powerPercent, 0, Qt::AlignTop);
            vlayout->addStretch();

            QScrollArea *scrollarea = new QScrollArea;
            scrollarea->setWidget(widget);
            scrollarea->setFixedWidth(300);
            scrollarea->setObjectName("scrollarea");
            scrollarea->setWidgetResizable(true);
            scrollarea->setFocusPolicy(Qt::NoFocus);
            scrollarea->setFrameStyle(QFrame::NoFrame);
            scrollarea->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            scrollarea->setContentsMargins(0, 0, 0, 0);
            scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            scrollarea->setStyleSheet("background-color: transparent;");

            m_mainLayout->addWidget(scrollarea, 0, Qt::AlignTop);

            QPushButton *button = new QPushButton(this);
            button->setText(tr("Advanced settings"));
            m_mainLayout->addWidget(button, 0, Qt::AlignBottom);

            connect(awakenDisplay, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenDisplayChanged);
            connect(awakenComputer, &SwitchItem::clicked, this, &PowerPopupWidget::onAwakenComputerChanged);
            connect(powerPercent, &SwitchItem::clicked, this, &PowerPopupWidget::requestPowerPrecent);

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

            m_showAni = new QPropertyAnimation(this, "size", this);
            m_showAni->setDuration(300);
            m_showAni->setStartValue(QSize(width(), 30));
            m_showAni->setEndValue(size());
            m_showAni->setEasingCurve(QEasingCurve::InOutCubic);

            m_hideAni = new QPropertyAnimation(this, "size", this);
            m_hideAni->setDuration(300);
            m_hideAni->setStartValue(size());
            m_hideAni->setEndValue(QSize(width(), 30));
            m_hideAni->setEasingCurve(QEasingCurve::InOutCubic);

            connect(m_hideAni, &QPropertyAnimation::finished, this, &PowerPopupWidget::requestHidePopup);

            m_effect = new QGraphicsOpacityEffect;
            setGraphicsEffect(m_effect);

            m_effectShowAni = new QPropertyAnimation(m_effect, "opacity", this);
            m_effectHideAni = new QPropertyAnimation(m_effect, "opacity", this);

            m_effectShowAni->setDuration(250);
            m_effectShowAni->setStartValue(0.0);
            m_effectShowAni->setEndValue(1.0);
            m_effectShowAni->setEasingCurve(QEasingCurve::InBack);

            m_effectHideAni->setDuration(250);
            m_effectHideAni->setStartValue(1.0);
            m_effectHideAni->setEndValue(0.0);
            m_effectHideAni->setEasingCurve(QEasingCurve::OutBack);
        }

        void PowerPopupWidget::showAni()
        {
            show();
            m_showAni->start();
            m_effectShowAni->start();
        }

        void PowerPopupWidget::hideAni()
        {
            m_hideAni->start();
            m_effectHideAni->start();
        }

        void PowerPopupWidget::onAwakenDisplayChanged(const bool state) {

        }

        void PowerPopupWidget::onAwakenComputerChanged(const bool state) {

        }

        QGroupBox *PowerPopupWidget::createPowerStateGrp()
        {
            QGroupBox * groupBox = new QGroupBox(tr("Switching system power"));

            QRadioButton *radio1 = new QRadioButton(tr("High performance"));
            QRadioButton *radio2 = new QRadioButton(tr("Balance"));
            QRadioButton *radio3 = new QRadioButton(tr("Power saving"));

            radio2->setChecked(true);

            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(radio2);
            layout->addWidget(radio3);
            layout->addWidget(radio1);

            groupBox->setLayout(layout);

            return groupBox;
        }
    }
}
