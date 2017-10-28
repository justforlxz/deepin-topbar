#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include "item/contentmodule.h"

#include <QWidget>
#include <QLabel>

namespace dtb {
namespace systeminfo {
class SystemInfoWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit SystemInfoWidget(QWidget *parent = 0);

private:
    const QString converSpeed(const int value);

private:
    QLabel *m_rx;
    QLabel *m_tx;
};
}
}

#endif // SYSTEMINFOWIDGET_H
