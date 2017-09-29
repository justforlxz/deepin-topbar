#ifndef AccountPOPUPWIDGET_H
#define AccountPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>


namespace dtb {
namespace widgets {
class FontLabel;
}

namespace account {

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
    widgets::FontLabel *m_lock;
    widgets::FontLabel *m_logout;
    widgets::FontLabel *m_reboot;
    widgets::FontLabel *m_suspend;
    widgets::FontLabel *m_shutdown;
};

}
}

#endif // AccountPOPUPWIDGET_H
