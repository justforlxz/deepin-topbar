#include "entry.h"
#include <QHBoxLayout>
#include <QIcon>

Entry::Entry(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_normalIcon = new QLabel;
    m_title = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_normalIcon, 0, Qt::AlignVCenter);
    mainLayout->addWidget(m_title, 0, Qt::AlignVCenter);

    setStyleSheet("QLabel {"
                  "font: 14px;"
                  "}");

    setLayout(mainLayout);
}

void Entry::setNormalIcon(const QIcon &normalIcon)
{
    m_normalIcon->setPixmap(normalIcon.pixmap(size()));
}

void Entry::setText(const QString &text)
{
    m_title->setText(text);
}
