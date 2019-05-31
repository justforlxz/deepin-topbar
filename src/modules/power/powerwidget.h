#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "frame/item/contentmodule.h"

#include <QWidget>
#include <QLabel>
#include <QMenu>
#include <com_deepin_daemon_power.h>
#include <com_deepin_system_systempower.h>

using SystemPowerInter = com::deepin::system::Power;
using PowerInter = com::deepin::daemon::Power;

namespace dtb {

namespace widgets {
class FontLabel;
}

namespace power {

// from https://upower.freedesktop.org/docs/Device.html#Device:State
enum BatteryState
{
    UNKNOWN = 0,
    CHARGING = 1,
    DISCHARGING = 2,
    EMPTY = 3,
    FULLY_CHARGED = 4,
    PENDING_CHARGE = 5,
    PENDING_DISCHARGE = 6
};

class PowerWidgetAction;

class PowerWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);

    inline QMenu *menu() { return m_menu;}

signals:
    void requestHidePopupWindow();
    void requestEnableLastTime(const bool enabled);

public slots:
    void updateBatteryIcon();
    void onActionHandle(const QString &action);
    void setEnableLastTime(const bool enable);
    void refreshTipsData();

private:
    void initMenu();

private:
    PowerWidgetAction *m_powerActionWidget;
    QLabel *m_batteryIcon;
    QLabel *m_battery;
    PowerInter* m_powerInter;
    SystemPowerInter *m_systemPowerInter;
    QMenu *m_menu;
    QAction *m_sourceAction;
    bool m_showLastTime;
};
}
}

#endif // POWERWIDGET_H
