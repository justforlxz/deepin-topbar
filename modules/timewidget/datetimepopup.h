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

    QString format() const;
    void setFormat(const QString &format);

signals:
    void requestDateFormat(const bool state);
    void requestHide();
    void requestIsCenterChanged(const bool state);
    void requestFormatChanged(const QString &format);

public slots:
    void onDateFormatChanged(const bool state);

private:
    SwitchItem *m_dateBtn;
    SwitchItem *m_posBtn;
    SwitchItem *m_formatBtn;
    bool m_isCenter;
    bool m_is24Format;
    QString m_format;
};
}
}

#endif // DATETIMEPOPUP_H
