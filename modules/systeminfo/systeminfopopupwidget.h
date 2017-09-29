#ifndef SYSTEMINFOPOPUPWIDGET_H
#define SYSTEMINFOPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class SystemInfoPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SystemInfoPopupWidget(QWidget *parent = 0);

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};

#endif // SYSTEMINFOPOPUPWIDGET_H
