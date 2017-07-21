#include "pluginsitem.h"
#include <QHBoxLayout>
#include <QDBusPendingReply>
#include <QDBusObjectPath>
#include <QPoint>
#include <QMouseEvent>

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent) :
    Item(parent),
    m_pluginInter(pluginInter),
    m_centralWidget(pluginInter->itemWidget(itemKey)),
    m_itemKey(itemKey)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_centralWidget);

    setLayout(mainLayout);
}

PluginsItem::~PluginsItem()
{

}

PluginsItem::ItemType PluginsItem::itemType() const
{
    if (m_pluginInter->pluginName() == "indicator")
        return Indicator;
    if (m_pluginInter->pluginName() == "datetime")
        return DateTime;
    if (m_pluginInter->pluginName() == "notify")
        return Notify;

    return Plugin;
}

const QString PluginsItem::name() const
{
    return m_pluginInter->pluginName();
}

void PluginsItem::finished()
{
    m_pluginInter->finished();
}

QWidget *PluginsItem::popupTips()
{
    return m_pluginInter->itemPopupApplet(m_itemKey);
}

PluginsItemInterface *PluginsItem::itemInter()
{
    return m_pluginInter;
}

void PluginsItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        showTips();
}
