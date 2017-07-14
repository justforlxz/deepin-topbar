#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <QLabel>

class SystemInfoWidget : public QLabel
{
    Q_OBJECT
public:
    explicit SystemInfoWidget(QWidget *parent = 0);
};

#endif // SYSTEMINFOWIDGET_H
