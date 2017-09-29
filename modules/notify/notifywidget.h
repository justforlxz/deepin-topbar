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

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    widgets::FontLabel *m_NotifyIcon;
};
}
}



#endif // NOTIFYWIDGET_H
