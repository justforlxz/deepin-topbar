#ifndef DATETIMEPOPUP_H
#define DATETIMEPOPUP_H

#include "switchitem.h"
#include <QWidget>

class DateTimePopup : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePopup(QWidget *parent = 0);

signals:
    void requestDateFormat(const bool state);

public slots:
    void onDateFormatChanged(const bool state);

private:
    SwitchItem *_DateBtn;
};

#endif // DATETIMEPOPUP_H
