#ifndef AccountPOPUPWIDGET_H
#define AccountPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class AccountPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountPopupWidget(QWidget *parent = 0);

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};

#endif // AccountPOPUPWIDGET_H
