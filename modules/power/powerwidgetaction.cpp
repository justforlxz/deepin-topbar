#include "powerwidgetaction.h"
#include "../widgets/switchitem.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSize>
#include <QScrollArea>
#include <QRadioButton>
#include <QFile>
#include <QProcess>

using namespace topbar::widgets;

namespace dtb {
namespace power {
PowerWidgetAction::PowerWidgetAction(QWidget *parent) : QWidgetAction(parent) {
    initUI();
}

QWidget *PowerWidgetAction::createWidget(QWidget *parent)
{
    m_content->setParent(parent);
    return m_content;
}

void PowerWidgetAction::initUI()
{
    m_mainLayout = new QVBoxLayout;
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(7);

    m_content = new QWidget;
    m_content->setLayout(m_mainLayout);
}
}
}
