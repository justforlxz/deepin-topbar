#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include <darrowrectangle.h>
#include <DWindowManagerHelper>

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

private:
    DWindowManagerHelper *m_wmHelper;
};

#endif // ITEMPOPUPWINDOW_H
