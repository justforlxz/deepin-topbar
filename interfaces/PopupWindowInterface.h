#ifndef POPUPWINDOWINTERFACE_H
#define POPUPWINDOWINTERFACE_H

#include <QObject>

class PopupWindowInterface : public QObject
{
    Q_OBJECT
public:
    explicit PopupWindowInterface(QObject *parent = 0);

signals:

public slots:
};

#endif // POPUPWINDOWINTERFACE_H