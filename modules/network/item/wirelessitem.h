#ifndef WIRELESSITEM_H
#define WIRELESSITEM_H

#include "deviceitem.h"
#include "applet/wirelessapplet.h"

#include <QHash>

namespace dtb {
namespace network {
class WirelessItem : public DeviceItem
{
    Q_OBJECT

public:
    explicit WirelessItem(const QString &path);
    ~WirelessItem();

    NetworkDevice::NetworkType type() const;
    NetworkDevice::NetworkState state() const;
    QWidget *itemApplet();
    QWidget *itemPopup();

protected:
    bool eventFilter(QObject *o, QEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    const QPixmap iconPix(const int size);
    const QPixmap cachedPix(const QString &key, const int size);

private slots:
    void init();
    void adjustHeight();

private:
    QHash<QString, QPixmap> m_icons;

    QTimer *m_refershTimer;
    QWidget *m_wirelessApplet;
    QLabel *m_wirelessPopup;
    WirelessList *m_APList;
};
}
}

#endif // WIRELESSITEM_H
