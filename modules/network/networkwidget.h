#ifndef NetworkWIDGET_H
#define NetworkWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

namespace dtb {
namespace network {
class DeviceItem;
class NetworkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkWidget(QWidget *parent = 0);

    void addItem(DeviceItem *item);
    void remove(DeviceItem *item);

private:
    void initUI();

private:
    QHBoxLayout *m_layout;
    QList<DeviceItem*> m_devices;
};
}
}

#endif // NetworkWIDGET_H
