#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QLabel>

class DateTimeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

public slots:
    void updateTime();

private:
    QDateTime *m_dateTime;
};

#endif // DATETIMEWIDGET_H
