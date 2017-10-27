#include "notifywidget.h"
#include "fontlabel.h"
#include <QIcon>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>

using namespace dtb;
using namespace dtb::widgets;
using namespace dtb::notify;

NotifyWidget::NotifyWidget(QWidget *parent) : QLabel(parent)
{
      setFixedSize(30, 26);

      m_NotifyIcon = new FontLabel;
      m_NotifyIcon->setFixedSize(30, 22);
      m_NotifyIcon->setIcon(QChar(0xEA41), 16);

      m_NotifyIcon->setStyleSheet("QLabel {"
                                  "color: rgb(67, 67, 62);"
                                  "}");

      QHBoxLayout *layout = new QHBoxLayout;

      layout->setMargin(2);
      layout->setSpacing(0);
      layout->addWidget(m_NotifyIcon, 0, Qt::AlignCenter);

      setLayout(layout);
}
