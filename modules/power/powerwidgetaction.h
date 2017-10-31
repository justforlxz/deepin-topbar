#ifndef POWERWIDGETACTION_H
#define POWERWIDGETACTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QGroupBox>

namespace dtb {
namespace power {
class PowerWidgetAction : public QWidget
{
    Q_OBJECT
public:
    explicit PowerWidgetAction(QWidget *parent = nullptr);

private:
    void initUI();

private:
    QVBoxLayout *m_mainLayout;
};
}
}

#endif // POWERWIDGETACTION_H
