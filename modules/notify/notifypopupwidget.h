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

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private slots:
    void onScreenChanged();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};
}
}

#endif // NOTIFYPOPUPWIDGET_H
