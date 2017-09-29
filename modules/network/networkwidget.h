#ifndef NetworkWIDGET_H
#define NetworkWIDGET_H

#include <QLabel>

class NetworkWidget : public QLabel
{
    Q_OBJECT
public:
    explicit NetworkWidget(QWidget *parent = 0);
};

#endif // NetworkWIDGET_H
