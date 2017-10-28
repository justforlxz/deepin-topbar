#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "item/contentmodule.h"

#include <QWidget>
#include <QLabel>
#include <QMenu>

class DBusPower;

namespace dtb {

namespace widgets {
class FontLabel;
}

namespace power {

class PowerWidgetAction;

class PowerWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);

    inline QMenu *menu() { return m_menu;}

public slots:
    void updateBatteryIcon();

private:
    void initMenu();

private:
    PowerWidgetAction *m_powerActionWidget;
    widgets::FontLabel *m_batteryIcon;
    QLabel *m_battery;
    DBusPower* m_powerInter;
    QMenu *m_menu;
};
}
}

#endif // POWERWIDGET_H
