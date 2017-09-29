#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include <QWidget>
#include <QLabel>

class DBusPower;

namespace dtb {

namespace widgets {
class FontLabel;
}

namespace power {

class PowerPopupWidget;

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
    widgets::FontLabel *m_batteryIcon;
    QLabel *m_battery;
    DBusPower* m_powerInter;
    bool m_enter = false;
};
}
}

#endif // POWERWIDGET_H
