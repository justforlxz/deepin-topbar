#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include <QLabel>

namespace dtb {
namespace widgets {

class FontLabel;
}

namespace notify {
class NotifyWidget : public QLabel
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
