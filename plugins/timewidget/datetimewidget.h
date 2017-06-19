#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "datetimepopup.h"
#include <QWidget>
#include <QLabel>

class DateTimeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

    DateTimePopup *popupWidget();

public slots:
    void updateTime();

private:
    QLabel *m_timeLbl;
    QDateTime *m_dateTime;
    DateTimePopup *popup;
    bool m_24HourFormat;
};

#endif // DATETIMEWIDGET_H
