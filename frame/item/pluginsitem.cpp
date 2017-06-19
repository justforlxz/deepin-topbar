#include "pluginsitem.h"
#include "dbus/dbusmenu.h"
#include <QHBoxLayout>
#include <QDBusPendingReply>
#include <QDBusObjectPath>
#include <QPoint>
#include <QMouseEvent>

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent) :
    Item(parent),
    m_pluginInter(pluginInter),
    m_centralWidget(pluginInter->itemWidget(itemKey)),
    m_itemKey(itemKey),
    m_menuManagerInter(new DBusMenuManager(this))
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

    return Plugin;
}

const QString PluginsItem::name() const
{
    return m_pluginInter->pluginName();
}

QWidget *PluginsItem::popupTips()
{
    return m_pluginInter->itemTipsWidget(m_itemKey);
}

void PluginsItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    showTips();
}
