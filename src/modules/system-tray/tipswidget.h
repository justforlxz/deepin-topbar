#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include "frame/item/contentmodule.h"

#include <QWidget>
#include <QBoxLayout>

#define TrayWidgetWidth 26
#define TrayWidgetHeight 26

class AbstractTrayWidget;
class TrayApplet : public ContentModule
{
    Q_OBJECT

public:
    explicit TrayApplet(QWidget *parent = 0);

    void clear();
    void addWidget(AbstractTrayWidget *widget);
    void addWidgets(QList<AbstractTrayWidget *> widgets);
    void trayWidgetRemoved(AbstractTrayWidget *widget);

private:
    QBoxLayout *m_mainLayout;
};

#endif // TIPSWIDGET_H
