#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include "../interfaces/pluginsiteminterface.h"

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

    void setItemInter(PluginsItemInterface* itemInter);
    void setContent(QWidget *content);

    void showAnimation();
    void hideAnimation();

public slots:
    void show(const QPoint &pos);
    void show(const int x, const int y);

private slots:
    void compositeChanged();
    bool containsPoint(const QPoint &point) const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

private:
    PluginsItemInterface *m_itemInter;
    DWindowManagerHelper *m_wmHelper;
    XMouseArea *m_mouseArea;
    QString m_key;
    QWidget *m_content;
    QGraphicsOpacityEffect *m_effect;
    QPropertyAnimation *showAni;
    QPropertyAnimation *hideAni;
    QPropertyAnimation *sizeChangeAni_w;
    QPropertyAnimation *sizeChangeAni_h;
    QSize m_size;
};

#endif // ITEMPOPUPWINDOW_H
