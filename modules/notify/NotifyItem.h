#ifndef NOTIFYITEM_H
#define NOTIFYITEM_H

#include <QWidget>
#include <QJsonObject>

class NotifyItem : public QWidget
{
    Q_OBJECT
public:
    explicit NotifyItem(const QJsonObject &json, QWidget *parent = 0);

signals:

public slots:
};

#endif // NOTIFYITEM_H
