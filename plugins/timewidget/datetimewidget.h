#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QLabel>

class DateTimeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);

public slots:
    void updateTime();
};

#endif // DATETIMEWIDGET_H
