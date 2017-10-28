#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include "item/contentmodule.h"
#include <QLabel>

namespace dtb {
namespace widgets {

class FontLabel;
}

namespace notify {
class NotifyWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit NotifyWidget(QWidget *parent = 0);

private:
    widgets::FontLabel *m_NotifyIcon;
};
}
}



#endif // NOTIFYWIDGET_H
