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

signals:
    void requestHidePopupWindow();

public slots:
    void updateBatteryIcon();
    void onActionHandle(const QString &action);

private:
    void initMenu();

private:
    PowerWidgetAction *m_powerActionWidget;
    QLabel *m_batteryIcon;
    QLabel *m_battery;
    DBusPower* m_powerInter;
    QMenu *m_menu;
    QAction *m_sourceAction;
};
}
}

#endif // POWERWIDGET_H
