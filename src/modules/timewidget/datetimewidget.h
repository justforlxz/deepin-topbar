#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include "frame/item/contentmodule.h"

#include <QWidget>
#include <QLabel>
#include <QSettings>

namespace Plugin {
namespace DateTime {
class DateTimeWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit DateTimeWidget(QWidget *parent = 0);
    ~DateTimeWidget();

public slots:
    void set24HourFormat(bool is24HourFormat);
    void setFormat(const QString &value);

private slots:
    void updateTime();

private:
    QDateTime *m_dateTime;
    bool m_24HourFormat;
    QString m_format;
    QLabel *m_timeLbl;
};
}
}

#endif // DATETIMEWIDGET_H
