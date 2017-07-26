#ifndef NetworkPOPUPWIDGET_H
#define NetworkPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class NetworkPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPopupWidget(QWidget *parent = 0);

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};

#endif // NetworkPOPUPWIDGET_H
