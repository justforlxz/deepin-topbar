#ifndef POWERPOPUPWIDGET_H
#define POWERPOPUPWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

namespace Plugins {
    namespace Power {
        class PowerPopupWidget : public QWidget
        {
            Q_OBJECT
        public:
            explicit PowerPopupWidget(QWidget *parent = nullptr);

        signals:

        public slots:
            void onAwakenDisplayChanged(const bool state);
            void onAwakenComputerChanged(const bool state);
        private:
            QVBoxLayout *m_mainLayout;
        };
    }
}

#endif // POWERPOPUPWIDGET_H
