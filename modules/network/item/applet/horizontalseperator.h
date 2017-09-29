#ifndef HORIZONTALSEPERATOR_H
#define HORIZONTALSEPERATOR_H

#include <QWidget>

class HorizontalSeperator : public QWidget
{
    Q_OBJECT

public:
    explicit HorizontalSeperator(QWidget *parent = 0);

    void setColor(const QColor color);

protected:
    void paintEvent(QPaintEvent *e);

private:
    QColor m_color;
};

#endif // HORIZONTALSEPERATOR_H
