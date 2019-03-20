#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include "frame/item/contentmodule.h"

#include <QWidget>
#include <QLabel>

namespace dtb {
namespace systeminfo {
class SystemInfoModel;
class SystemInfoWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit SystemInfoWidget(QWidget *parent = 0);

    void setModel(SystemInfoModel *model);

private:
    const QString converSpeed(const int value);
    const QString formatPercent(int percent);
private:
    SystemInfoModel *m_model;
    QLabel *m_rx;
    QLabel *m_tx;
    QLabel *m_cpu;
    QLabel *m_mem;
    QLabel *m_swap;
};
}
}

#endif // SYSTEMINFOWIDGET_H
