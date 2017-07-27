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

const QRect PluginsItem::popupMarkGeometry() const
{
    return QRect(mapToGlobal(pos()), size());
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

void PluginsItem::showTips()
{
    QWidget * const content = popupTips();
    if (!content)
        return;

    showPopupWindow(content);
}

void PluginsItem::showPopupWindow(QWidget * const content)
{
    ItemPopupWindow *popup = PopupWindow.get();
    popup->setItemInter(itemInter());
    popup->setContent(content);

    PopupWindow->setVisible(true);

    popup->setRect(popupMarkGeometry());
}

void PluginsItem::hidePopup()
{
    ItemPopupWindow *popup = PopupWindow.get();
    PopupWindow->setVisible(false);
    popup->setVisible(false);
}
