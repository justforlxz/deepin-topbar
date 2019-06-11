#include "powermodel.h"

using namespace dtb;
using namespace dtb::power;

PowerModel::PowerModel(QObject *parent) : QObject(parent)
{

}

void PowerModel::setShowPercentage(bool showPercentage)
{
    if (m_showPercentage == showPercentage) return;

    m_showPercentage = showPercentage;

    emit showPercentageChanged(showPercentage);
}

void PowerModel::setBatteryStateInfo(const BatteryState &batteryStateInfo)
{
    if (m_batteryStateInfo == batteryStateInfo) return;

    m_batteryStateInfo = batteryStateInfo;

    emit batteryStateInfoChanged(batteryStateInfo);
}

void PowerModel::setbatteryPercentage(const double batteryPercentage)
{
    m_batteryPercentage = batteryPercentage;

    emit batteryPercentageChanged(batteryPercentage);
}
