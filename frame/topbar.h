#ifndef TOPBAR_H
#define TOPBAR_H

#include <QFrame>
#include <QHBoxLayout>

class TopBar : public QFrame
{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = 0);

signals:

public slots:

private:
    QHBoxLayout *m_mainLayout;
};

#endif // TOPBAR_H
