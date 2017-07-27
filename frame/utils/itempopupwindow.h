#ifndef ITEMPOPUPWINDOW_H
#define ITEMPOPUPWINDOW_H

#include <QVariantAnimation>
#include <DBlurEffectWidget>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

class ItemPopupWindow : public Dtk::Widget::DBlurEffectWidget
{
    Q_OBJECT

public:
    explicit ItemPopupWindow(QWidget *parent = 0);
    ~ItemPopupWindow();

    void setContent(QWidget *content);

public slots:
    void setRect(const QRect &rect);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QWidget *m_lastWidget;
    QSize m_size;
    bool m_isVisiable = false;
    QPoint m_point;
    QVariantAnimation *m_moveAni;
    QHBoxLayout *m_layout;
};

#endif // ITEMPOPUPWINDOW_H
