#ifndef POWERWIDGET_H
#define POWERWIDGET_H

#include "powerpopupwidget.h"
#include <QWidget>

namespace Plugins {
namespace Power {
class PowerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidget(QWidget *parent = nullptr);

    QWidget *popup();

signals:

public slots:

private:
    PowerPopupWidget *m_popup;
};

}
}

#endif // POWERWIDGET_H
