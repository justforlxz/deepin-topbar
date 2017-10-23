#ifndef NOTIFYPOPUPWIDGET_H
#define NOTIFYPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

namespace dtb {
namespace notify {
class NotifyPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotifyPopupWidget(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private slots:
    void onScreenChanged();

private:
    void initUI();
    void initConnect();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};
}
}

#endif // NOTIFYPOPUPWIDGET_H
