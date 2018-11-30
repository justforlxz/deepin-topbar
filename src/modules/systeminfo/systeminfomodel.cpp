#include "systeminfomodel.h"

using namespace dtb;
using namespace dtb::systeminfo;

SystemInfoModel::SystemInfoModel(QObject *parent) : QObject(parent)
{

}

void SystemInfoModel::setCputime(int cputime)
{
    m_cputime = cputime;

    emit cputimeChanged(cputime);
}
