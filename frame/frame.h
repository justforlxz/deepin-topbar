#ifndef FRAME_H
#define FRAME_H

#include <QFrame>

class Frame : public QFrame
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);

public slots:
    void registerDesktop();

};

#endif // FRAME_H
