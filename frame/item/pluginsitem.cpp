#include "pluginsitem.h"
#include "dbus/dbusmenu.h"
#include <QHBoxLayout>
#include <QDBusPendingReply>
#include <QDBusObjectPath>
#include <QPoint>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent) :
    Item(parent),
    m_pluginInter(pluginInter),
    m_centralWidget(pluginInter->itemWidget(itemKey)),
    m_itemKey(itemKey),
    m_eventMonitor(new EventMonitor(this)),
    m_menuManagerInter(new DBusMenuManager(this))
{
    m_eventMonitor->start();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_centralWidget);

    setLayout(mainLayout);

    connect(m_eventMonitor, &EventMonitor::buttonPress, this, [=] (int x, int y) {
        ItemPopupWindow *popup = PopupWindow.get();
        if (!containsPoint(QPoint(x, y)) && popup->isVisible()) {
            m_pluginInter->popupHide();
        }
    });
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
    QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    ItemPopupWindow *popup = PopupWindow.get();

    // check popup is last right
    if (popup->width() + pos().x() >= screen.width()) {
        return QRect(QPoint(pos().x() - popup->width() + width(), height()), size());
    } else {
        return QRect(QPoint(pos().x(), height()), size());
    }
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
        showPopup();

    if (event->button() == Qt::RightButton)
        showContextMenu();
}

void PluginsItem::showPopup()
{
    QWidget * const content = popupTips();
    if (!content)
        return;

    showPopupWindow(content);
}

void PluginsItem::showPopupWindow(QWidget * const content)
{
    ItemPopupWindow *popup = PopupWindow.get();
    popup->setContent(content);
    m_pluginInter->popupShow();
    PopupWindow->setVisible(true);

    popup->setRect(popupMarkGeometry());
}

void PluginsItem::hidePopup()
{
    ItemPopupWindow *popup = PopupWindow.get();
    PopupWindow->setVisible(false);
    popup->setVisible(false);
}

QMenu *PluginsItem::contextMenu() const
{
    return m_pluginInter->itemContextMenu(m_itemKey);
}

bool PluginsItem::containsPoint(const QPoint &point) const
{
    // if click self;
    QRect self(m_pluginInter->itemWidget("")->mapToGlobal(m_pluginInter->itemWidget("")->pos()), m_pluginInter->itemWidget("")->size());
    if (isVisible() && self.contains(point))
        return false;

    QRect s = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    QRegion screen(s.x(), s.y(), s.width(), 27);
    ItemPopupWindow *popup = PopupWindow.get();
    if (screen.contains(point) || popup->geometry().contains(point))
        return true;

    return false;
}

void PluginsItem::showContextMenu()
{
    QMenu* menu = contextMenu();
    if (!menu)
        return;

    const QRect r = popupMarkGeometry();
    const QPoint p = QPoint(r.x(), r.y());

    menu->exec(p);

    hidePopup();
}

