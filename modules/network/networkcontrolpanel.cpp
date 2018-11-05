#include "networkcontrolpanel.h"
#include "networklistmodel.h"
#include "networklistview.h"

using namespace dtb;
using namespace dtb::network;

NetworkControlPanel::NetworkControlPanel(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
    , m_listView(new NetworkListView)
{
    m_layout->setMargin(0);
    m_layout->setSpacing(0);

    m_layout->addWidget(m_listView);

    m_listView->setFixedSize(400, 600);

    setLayout(m_layout);
}

void NetworkControlPanel::setModel(NetworkListModel * const model)
{
    m_listModel = model;
    m_listView->setModel(model);

    connect(m_listView, &NetworkListView::entered, model, &NetworkListModel::setHoverIndex);
}
