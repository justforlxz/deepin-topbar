#include "switchitem.h"
#include <QHBoxLayout>

namespace dtb {
namespace widgets {
SwitchItem::SwitchItem(QWidget *parent) : QWidget(parent) {
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedHeight(30);
    m_text = new QLabel;
    m_switch = new DSwitchButton;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);

    layout->addWidget(m_text);
    layout->addStretch();
    layout->addSpacing(10);
    layout->addWidget(m_switch);

    setLayout(layout);

    connect(m_switch, &DSwitchButton::checkedChanged, this, &SwitchItem::clicked);
}

void SwitchItem::setText(const QString &text) {
    m_text->setText(text);
}

void SwitchItem::setCheck(const bool state) {
    m_switch->blockSignals(true);
    m_switch->setChecked(state);
    m_switch->blockSignals(false);
}

void SwitchItem::setValue(const QString &value) {
    m_value = value;
}

}
}
