#ifndef WIREDITEM_H
#define WIREDITEM_H

#include "deviceitem.h"

#include <QWidget>
#include <QLabel>
#include <QTimer>

class WiredItem : public DeviceItem
{
    Q_OBJECT

public:
    explicit WiredItem(const QString &path);

    NetworkDevice::NetworkType type() const override;
    NetworkDevice::NetworkState state() const override;
    QWidget *itemPopup() override;
    const QString itemCommand() const override;

protected:
    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;

private slots:
    void refreshIcon() override;
    void reloadIcon();
    void activeConnectionChanged();
    void deviceStateChanged(const NetworkDevice &device);

private:
    bool m_connected;
    QPixmap m_icon;

    QLabel *m_itemTips;
    QTimer *m_delayTimer;
};

#endif // WIREDITEM_H
