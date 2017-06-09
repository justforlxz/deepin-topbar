#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include <QLabel>

class TimeWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TimeWidget(QWidget *parent = 0);

signals:

public slots:
    void onTimeout();
};

#endif // TIMEWIDGET_H
