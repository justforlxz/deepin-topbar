#ifndef NETWORKCONTROLPANEL_H
#define NETWORKCONTROLPANEL_H

#include <QWidget>
#include <QVBoxLayout>

namespace dtb {
namespace network {
class NetworkListView;
class NetworkListModel;
class NetworkControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkControlPanel(QWidget *parent = nullptr);

    void setModel(NetworkListModel * const model);

signals:

public slots:

private:
    QVBoxLayout *m_layout;
    NetworkListView *m_listView;
    NetworkListModel *m_listModel;
};
}
}

#endif // NETWORKCONTROLPANEL_H
