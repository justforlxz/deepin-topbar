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

    bool isCenter() const;
    void setIsCenter(bool isCenter);

    bool is24Format() const;
    void setIs24Format(bool is24Format);

signals:
    void requestDateFormat(const bool state);
    void requestHide();
    void requestIsCenterChanged(const bool state);

public slots:
    void onDateFormatChanged(const bool state);

private:
    SwitchItem *m_dateBtn;
    SwitchItem *m_posBtn;
    bool m_isCenter;
    bool m_is24Format;
};
}
}

#endif // DATETIMEPOPUP_H
