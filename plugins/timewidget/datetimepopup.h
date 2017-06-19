#ifndef DATETIMEPOPUP_H
#define DATETIMEPOPUP_H

#include "switchitem.h"
#include <QWidget>
#include <QList>

class DateTimePopup : public QWidget
{
    Q_OBJECT
public:
    explicit DateTimePopup(QWidget *parent = 0);

signals:
    void requestDateFormat(const bool state);

public slots:
    void onDateFormatChanged(const bool state);
    void onSetDefaultDateFormat(int format);

private:
    QList<SwitchItem*> m_buttonGrp;
};

#endif // DATETIMEPOPUP_H
