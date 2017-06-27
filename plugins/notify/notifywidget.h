#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include <QLabel>

class NotifyWidget : public QLabel
{
    Q_OBJECT
public:
    explicit NotifyWidget(QWidget *parent = 0);
};

#endif // NOTIFYWIDGET_H
