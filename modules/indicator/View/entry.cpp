#include "entry.h"
#include <QHBoxLayout>
#include <QIcon>

namespace Plugin {
namespace Indicator {

Entry::Entry(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_normalIcon = new QLabel;
    m_title = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(5);

    mainLayout->addWidget(m_normalIcon, 0, Qt::AlignVCenter | Qt::AlignLeft);
    mainLayout->addWidget(m_title, 0, Qt::AlignVCenter | Qt::AlignLeft);

    setStyleSheet("QLabel {"
                  "font: 14px;"
                  "color: rgb(67, 67, 62);"
                  "font-weight: 500;"
                  "}");

    setLayout(mainLayout);
}

void Entry::setNormalIcon(const QIcon &normalIcon)
{
    m_normalIcon->setPixmap(normalIcon.pixmap(QSize(20, 20)));
}

void Entry::setText(const QString &text)
{
    m_title->setText(text);
}

}
}
