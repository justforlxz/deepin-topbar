#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <QWidget>
#include <QBoxLayout>

class TrayWidget;
class TrayApplet : public QWidget
{
    Q_OBJECT

public:
    explicit TrayApplet(QWidget *parent = 0);

    void clear();
    void addWidget(TrayWidget * widget);
    void addWidgets(QList<TrayWidget *> widgets);

private:
    QBoxLayout *m_mainLayout;
};

#endif // TIPSWIDGET_H
