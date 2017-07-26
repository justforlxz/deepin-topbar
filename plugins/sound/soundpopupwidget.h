#ifndef SoundPOPUPWIDGET_H
#define SoundPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class SoundPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SoundPopupWidget(QWidget *parent = 0);

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};

#endif // SoundPOPUPWIDGET_H
