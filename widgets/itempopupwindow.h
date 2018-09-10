#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include <QWidget>
#include <darrowrectangle.h>
#include <dregionmonitor.h>

DWIDGET_USE_NAMESPACE

class ItemPopupWindow : public DArrowRectangle
{
    Q_OBJECT
public:
    explicit ItemPopupWindow(QWidget *parent = nullptr);

    void show(int x, int y);

private:
    DRegionMonitor *m_regionMonitor;
};

#endif // ITEMPOPUPWINDOW_H
