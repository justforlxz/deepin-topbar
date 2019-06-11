#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "frame/item/contentmodule.h"

#include <QWidget>
#include <QLabel>
#include <QMenu>

namespace dtb {

namespace widgets {
class FontLabel;
}

namespace power {
class PowerModel;
class PowerWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);
    void setModel(PowerModel* model);

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
    PowerModel* m_model;
    QLabel *m_batteryIcon;
    QLabel *m_battery;
    QMenu *m_menu;
    QAction *m_sourceAction;
    bool m_showLastTime;
};
}
}

#endif // POWERWIDGET_H
