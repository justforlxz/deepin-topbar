#ifndef POWERMODEL_H
#define POWERMODEL_H

#include <QObject>

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

namespace dtb {
namespace power {
class PowerModel : public QObject
{
    Q_OBJECT
public:
    explicit PowerModel(QObject *parent = nullptr);

    inline bool showPercentage() const { return m_showPercentage; }
    inline BatteryState batteryStateInfo() const { return m_batteryStateInfo; }
    inline double batteryPercentage() const { return m_batteryPercentage; }

signals:
    void showPercentageChanged(bool showPercentage);
    void batteryStateInfoChanged(const BatteryState& info);
    void batteryPercentageChanged(const double& batteryPercentage);

public slots:
    void setShowPercentage(bool showPercentage);
    void setBatteryStateInfo(const BatteryState &batteryStateInfo);
    void setbatteryPercentage(const double batteryPercentage);

private:
    bool m_showPercentage;
    BatteryState m_batteryStateInfo;
    double m_batteryPercentage;
};
}
}

#endif // POWERMODEL_H
