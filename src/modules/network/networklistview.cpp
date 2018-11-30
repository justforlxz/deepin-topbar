#include "networklistview.h"
#include "networkdelegate.h"

using namespace dtb;
using namespace dtb::network;

NetworkListView::NetworkListView(QWidget *parent)
    : QListView(parent)
{
    setMouseTracking(true);
    setItemDelegate(new NetworkDelegate);
}
