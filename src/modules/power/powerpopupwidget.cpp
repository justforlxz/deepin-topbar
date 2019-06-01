#include "powerpopupwidget.h"

#include "widgets/settingsgroup.h"
#include "widgets/titlevalueitem.h"
#include "widgets/switchwidget.h"

#include <QVBoxLayout>

using namespace dtb;
using namespace dtb::power;
using namespace dtb::widgets;

PowerPopupWidget::PowerPopupWidget(QWidget *parent)
    : QWidget(parent)
    , m_powerSettingsGrp(new SettingsGroup)
    , m_sourceItem(new TitleValueItem)
    , m_rcentageSwitcher(new SwitchWidget(tr("Show percentage")))
{
    setFixedWidth(250);

    m_sourceItem->setTitle(tr("Power Source"));
    m_sourceItem->setValue(tr("Battery"));

    m_powerSettingsGrp->appendItem(m_sourceItem);
    m_powerSettingsGrp->appendItem(m_rcentageSwitcher);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addWidget(m_powerSettingsGrp);
    setLayout(layout);
}
