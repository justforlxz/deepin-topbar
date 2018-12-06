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

    void show(int x, int y) override;

protected:
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private:
    DRegionMonitor *m_regionMonitor;
};

#endif // ITEMPOPUPWINDOW_H
