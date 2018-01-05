#ifndef REFRESHACTION_H
#define REFRESHACTION_H

#include <QLabel>

namespace dtb {
namespace network {
class RefreshAction : public QLabel
{
    Q_OBJECT
public:
    explicit RefreshAction(QWidget *parent = nullptr);
    void setIsRefresh(const bool refresh);

signals:
    void refresh();
};
}
}

#endif // REFRESHACTION_H
