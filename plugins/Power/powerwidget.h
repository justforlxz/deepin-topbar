#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "DBus/dbuspower.h"
#include "powerpopupwidget.h"
#include "fontlabel.h"
#include <QWidget>
#include <QLabel>

namespace Plugins {
namespace Power {
class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);

    QWidget *popup();

signals:
    void requestHidePopup();

public slots:
    void updateBatteryIcon();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    PowerPopupWidget *m_popup;
    FontLabel *m_batteryIcon;
    QLabel *m_battery;
    DBusPower* m_powerInter;
    bool m_enter = false;
};
}
}

#endif // POWERWIDGET_H
