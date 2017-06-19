#include "powerwidget.h"

namespace Plugins {
namespace Power {

PowerWidget::PowerWidget(QWidget *parent) : QWidget(parent)
{
    m_popup = new PowerPopupWidget;
}

QWidget *PowerWidget::popup()
{
    return m_popup;
}

}
}
