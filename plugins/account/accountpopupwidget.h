#ifndef AccountPOPUPWIDGET_H
#define AccountPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class FontLabel;

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

private slots:
    void handleShutdownAction(const QString &action);
    void handleLockAction();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
    FontLabel *m_lock;
    FontLabel *m_logout;
    FontLabel *m_reboot;
    FontLabel *m_suspend;
    FontLabel *m_shutdown;
};

#endif // AccountPOPUPWIDGET_H
