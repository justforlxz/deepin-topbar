#ifndef FRAME_H
#define FRAME_H

#include <QFrame>
#include <DPlatformWindowHandle>

class Frame : public QFrame
{
    Q_OBJECT
public:
    explicit Frame(QWidget *parent = nullptr);

    DPlatformWindowHandle * handle();

public slots:
    void registerDesktop();

private:
    DPlatformWindowHandle *m_handle;
};

#endif // FRAME_H
