#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include <darrowrectangle.h>
#include <DWindowManagerHelper>
#include <com_deepin_api_xmousearea.h>

using namespace com::deepin::api;

DWIDGET_USE_NAMESPACE

class ItemPopupWindow : public Dtk::Widget::DArrowRectangle
{
    Q_OBJECT

public:
    explicit ItemPopupWindow(QWidget *parent = 0);
    ~ItemPopupWindow();

    void setContent(QWidget *content);

public slots:
    void show(const QPoint &pos);
    void show(const int x, const int y);

private slots:
    void compositeChanged();
    bool containsPoint(const QPoint &point) const;

private:
    DWindowManagerHelper *m_wmHelper;
    XMouseArea *m_mouseArea;
    QString m_key;
};

#endif // ITEMPOPUPWINDOW_H
