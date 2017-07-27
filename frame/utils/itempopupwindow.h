#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include "../interfaces/pluginsiteminterface.h"

#include <DBlurEffectWidget>
#include <com_deepin_api_xmousearea.h>
#include <QHBoxLayout>

using namespace com::deepin::api;

DWIDGET_USE_NAMESPACE

class ItemPopupWindow : public Dtk::Widget::DBlurEffectWidget
{
    Q_OBJECT

public:
    explicit ItemPopupWindow(QWidget *parent = 0);
    ~ItemPopupWindow();

    void setItemInter(PluginsItemInterface* itemInter);
    void setContent(QWidget *content);

public slots:
    void setRect(const QRect &rect);

private slots:
    bool containsPoint(const QPoint &point) const;

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    PluginsItemInterface *m_itemInter;
    XMouseArea *m_mouseArea;
    QString m_key;
    QWidget *m_lastWidget;
    QSize m_size;
    bool m_isVisiable = false;
    QPoint m_point;
    QVariantAnimation *m_moveAni;
    QHBoxLayout *m_layout;
};

#endif // ITEMPOPUPWINDOW_H
