#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include "fontlabel.h"

#include <QWidget>
#include <QLabel>

class SystemInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SystemInfoWidget(QWidget *parent = 0);

protected:
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    const QString converSpeed(const int value);

private:
    QLabel *m_rx;
    QLabel *m_tx;
    bool m_enter;
};

#endif // SYSTEMINFOWIDGET_H
