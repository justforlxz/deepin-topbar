#include "accountwidget.h"
#include "fontlabel.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

AccountWidget::AccountWidget(QWidget *parent) : QLabel(parent)
{
      setFixedSize(30, 26);

      setStyleSheet("QLabel {"
                    "background: transparent;"
                    "}"
                    "QLabel:hover {"
                    "background: #1E90FF;"
                    "}");

      m_AccountIcon = new FontLabel;
      m_AccountIcon->setFixedSize(30, 22);
      m_AccountIcon->setIcon(QChar(0xEA41), 16);

      m_AccountIcon->setStyleSheet("QLabel {"
                                  "color: rgb(67, 67, 62);"
                                  "}");

      QHBoxLayout *layout = new QHBoxLayout;

      layout->setMargin(2);
      layout->setSpacing(0);
      layout->addWidget(m_AccountIcon, 0, Qt::AlignCenter);

      setLayout(layout);

      installEventFilter(this);
}

bool AccountWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QMouseEvent::Enter) {
        m_AccountIcon->setStyleSheet("background: transparent;"
                                    "color: white;");
    }

    if (event->type() == QMouseEvent::Leave) {
        m_AccountIcon->setStyleSheet("background: transparent;"
                                    "color: rgb(67, 67, 62);");
    }

    return false;
}
