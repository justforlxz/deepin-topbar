#include "powerwidgetaction.h"
#include "widgets/switchitem.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSize>
#include <QScrollArea>
#include <QRadioButton>
#include <QFile>
#include <QProcess>

using namespace dtb::widgets;

namespace dtb {
namespace power {
PowerWidgetAction::PowerWidgetAction(QWidget *parent)
    : QWidget(parent)
{
    initUI();
}

void PowerWidgetAction::initUI()
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);


    setLayout(m_mainLayout);
}
}
}
