#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "DBus/dbuspower.h"
#include "powerpopupwidget.h"
#include <QWidget>
#include <QLabel>

namespace Plugins {
    namespace Power {
        class PowerWidget : public QWidget
        {
            Q_OBJECT
        public:
            explicit PowerWidget(QWidget *parent = nullptr);

            QWidget *popup();

        signals:

        public slots:
            void updateBatteryIcon();

        private:
            PowerPopupWidget *m_popup;
            QLabel *m_batteryIcon;
            QLabel *m_battery;
            DBusPower* m_powerInter;
        };
    }
}

#endif // POWERWIDGET_H
