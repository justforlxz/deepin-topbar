#ifndef NETWORKLISTVIEW_H
#define NETWORKLISTVIEW_H

#include <QListView>

namespace dtb {
namespace network {
class NetworkListView : public QListView
{
    Q_OBJECT
public:
    explicit NetworkListView(QWidget *parent = nullptr);

signals:

public slots:
};
}
}

#endif // NETWORKLISTVIEW_H
