#ifndef POWERWIDGETACTION_H
#define POWERWIDGETACTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QGroupBox>
#include <QWidgetAction>

namespace dtb {
namespace power {
class PowerWidgetAction : public QWidgetAction
{
    Q_OBJECT
public:
    explicit PowerWidgetAction(QWidget *parent = nullptr);

    QWidget * createWidget(QWidget *parent) Q_DECL_OVERRIDE;

private:
    void initUI();

private:
    QWidget *m_content;
    QVBoxLayout *m_mainLayout;
};
}
}

#endif // POWERWIDGETACTION_H
