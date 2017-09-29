#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include <QLabel>

class FontLabel;

class NotifyWidget : public QLabel
{
    Q_OBJECT
public:
    explicit NotifyWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    FontLabel *m_NotifyIcon;
};

#endif // NOTIFYWIDGET_H
