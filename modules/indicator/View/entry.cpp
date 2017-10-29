#include "entry.h"

#include <QHBoxLayout>
#include <QIcon>

namespace dtb {
namespace indicator {

Entry::Entry(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_title = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addSpacing(10);
    mainLayout->addWidget(m_title, 0, Qt::AlignVCenter | Qt::AlignLeft);

    setLayout(mainLayout);
}

void Entry::setText(const QString &text)
{
    m_title->setText(text);
}

}
}
