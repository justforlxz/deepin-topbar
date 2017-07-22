#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "datetimepopup.h"
#include <QWidget>
#include <QLabel>
#include <QSettings>

namespace Plugin {
namespace DateTime {
class DateTimeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

    DateTimePopup *popupWidget();

    bool isCenter();

public slots:
    void updateTime();

private:
    QDateTime *m_dateTime;
    DateTimePopup *popup;
    bool m_24HourFormat;
};
}
}

#endif // DATETIMEWIDGET_H
