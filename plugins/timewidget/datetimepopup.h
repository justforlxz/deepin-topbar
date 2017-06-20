#ifndef DATETIMEPOPUP_H
#define DATETIMEPOPUP_H

#include "../widgets/switchitem.h"
#include <QWidget>

using namespace topbar::widgets;

namespace Plugin {
    namespace DateTime {
        class DateTimePopup : public QWidget
        {
            Q_OBJECT
        public:
            explicit DateTimePopup(QWidget *parent = 0);

        signals:
            void requestDateFormat(const bool state);
            void requestHide();

        public slots:
            void onDateFormatChanged(const bool state);

        private:
            SwitchItem *_DateBtn;
        };
    }
}

#endif // DATETIMEPOPUP_H
