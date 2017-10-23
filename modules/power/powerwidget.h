#ifndef POWERWIDGET_H
#define POWERWIDGET_H

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

class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);

    inline QMenu *menu() { return m_menu;}

public slots:
    void updateBatteryIcon();

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    void initMenu();

private:
    PowerWidgetAction *m_powerActionWidget;
    widgets::FontLabel *m_batteryIcon;
    QLabel *m_battery;
    DBusPower* m_powerInter;
    bool m_enter = false;
    QMenu *m_menu;
};
}
}

#endif // POWERWIDGET_H
