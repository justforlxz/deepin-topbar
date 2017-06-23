#include "datetimepopup.h"
#include <QVBoxLayout>
#include <QProcess>
#include <QPushButton>

using namespace topbar::widgets;

namespace Plugin {
    namespace DateTime {
        DateTimePopup::DateTimePopup(QWidget *parent) : QWidget(parent) {
            setWindowFlags(Qt::FramelessWindowHint);

            _DateBtn = new SwitchItem;
            _DateBtn->setText(tr("Format Change"));

            QPushButton *btn = new QPushButton(tr("DateTime Settings"));

            QVBoxLayout *mainLayout = new QVBoxLayout;
            mainLayout->setMargin(5);
            mainLayout->setSpacing(5);

            mainLayout->addWidget(btn);
            mainLayout->addWidget(_DateBtn);

            setLayout(mainLayout);
            connect(_DateBtn, &SwitchItem::clicked, this, &DateTimePopup::requestDateFormat);
            connect(btn, &QPushButton::clicked, this, [=]{
                QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");
                emit requestHide();
            });
        }

        void DateTimePopup::onDateFormatChanged(const bool state) {
            _DateBtn->setCheck(state);
        }
    }
}
