#include "itempopupwindow.h"

ItemPopupWindow::ItemPopupWindow(QWidget *parent)
    : DArrowRectangle(DArrowRectangle::ArrowTop, parent)
    , m_regionMonitor(new DRegionMonitor(this))
{
    connect(m_regionMonitor, &DRegionMonitor::buttonRelease, this, [=] (const QPoint &p, const int flag){
        if (flag == 1 && !geometry().contains(mapFromGlobal(p))) {
            hide();
            m_regionMonitor->unregisterRegion();
            QWidget *w = getContent();
            if (w) w->setParent(nullptr);
        }
    }, Qt::QueuedConnection);
}

void ItemPopupWindow::show(int x, int y)
{
    DArrowRectangle::show(x, y);
    QTimer::singleShot(0, this, [=] {
        m_regionMonitor->registerRegion();
    });
}
