#include "notifywidget.h"
#include <QIcon>

NotifyWidget::NotifyWidget(QWidget *parent) : QLabel(parent)
{
      setFixedSize(24, 24);

      setPixmap(QIcon::fromTheme("view-list-details").pixmap(22, 22));

      setMargin(0);

      setStyleSheet("QLabel {"
                    "color: black;"
                    "background: transparent;"
                    "}"
                    "QLabel:hover {"
                    "color: white;"
                    "background: #1E90FF;"
                    "}");
}
