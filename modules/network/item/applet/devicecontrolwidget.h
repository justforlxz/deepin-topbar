#ifndef DEVICECONTROLWIDGET_H
#define DEVICECONTROLWIDGET_H

#include "horizontalseperator.h"

#include <QWidget>
#include <QLabel>

#include <dswitchbutton.h>

class DeviceControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceControlWidget(QWidget *parent = 0);

    void setDeviceName(const QString &name);
    void setDeviceEnabled(const bool enable);
//    void setSeperatorVisible(const bool visible);

signals:
    void deviceEnableChanged(const bool enable) const;

private:
    QLabel *m_deviceName;
    Dtk::Widget::DSwitchButton *m_switchBtn;
//    HorizontalSeperator *m_seperator;
};

#endif // DEVICECONTROLWIDGET_H
