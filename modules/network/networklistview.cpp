#include "networklistview.h"
#include "networkdelegate.h"

using namespace dtb;
using namespace dtb::network;

NetworkListView::NetworkListView(QWidget *parent)
    : QListView(parent)
{
    setItemDelegate(new NetworkDelegate);
}
