#ifndef POWERPOPUPWIDGET_H
#define POWERPOPUPWIDGET_H

#include <QWidget>

namespace Plugins {
    namespace Power {
        class PowerPopupWidget : public QWidget
        {
            Q_OBJECT
        public:
            explicit PowerPopupWidget(QWidget *parent = nullptr);

        signals:

        public slots:
        };
    }
}

#endif // POWERPOPUPWIDGET_H
