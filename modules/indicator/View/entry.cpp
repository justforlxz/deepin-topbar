#include "entry.h"

#include <QHBoxLayout>
#include <QIcon>

namespace dtb {
namespace indicator {

Entry::Entry(QWidget *parent) : QFrame(parent)
{
    setObjectName("Entry");

    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_title = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(10, 0, 10, 0);

    mainLayout->addWidget(m_title, 0, Qt::AlignVCenter | Qt::AlignLeft);

    setLayout(mainLayout);
}

void Entry::setText(const QString &text)
{
    m_title->setText(text);
}

}
}
