#include "refreshaction.h"

using namespace dtb;
using namespace dtb::network;

RefreshAction::RefreshAction(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    setContentsMargins(15, 0, 0, 0);
    setIsRefresh(false);
}

void RefreshAction::setIsRefresh(const bool refresh)
{
    setText(tr("List state: %1").arg(refresh ? tr("Refreshing...") : tr("No refresh")));
}
