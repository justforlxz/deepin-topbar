#include "pluginsitem.h"
#include "dbus/dbusmenu.h"
#include <QHBoxLayout>
#include <QDBusPendingReply>
#include <QDBusObjectPath>
#include <QPoint>
#include <QMouseEvent>

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent) :
    QWidget(parent),
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

void PluginsItem::invokedMenuItem(const QString &itemId, const bool checked)
{
    m_pluginInter->invokedMenuItem(m_itemKey, itemId, checked);
}

const QString PluginsItem::contextMenu() const
{
    return m_pluginInter->itemContextMenu(m_itemKey);
}

QWidget *PluginsItem::popupTips()
{
    return m_pluginInter->itemTipsWidget(m_itemKey);
}

void PluginsItem::showContextMenu()
{
    const QString menuJson = contextMenu();

    if (menuJson.isEmpty())
        return;

    QDBusPendingReply<QDBusObjectPath> result = m_menuManagerInter->RegisterMenu();

    result.waitForFinished();
    if (result.isError()) {
        qWarning() << result.error();
        return;
    }

    const QPoint p = popupMarkPoint();

    QJsonObject menuObject;
    menuObject.insert("x", QJsonValue(p.x()));
    menuObject.insert("y", QJsonValue(p.y()));
    menuObject.insert("isDockMenu", QJsonValue(true));
    menuObject.insert("menuJsonContent", QJsonValue(menuJson));
    menuObject.insert("direction", "top");

    const QDBusObjectPath path = result.argumentAt(0).value<QDBusObjectPath>();
    DBusMenu *menuInter = new DBusMenu(path.path(), this);

    connect(menuInter, &DBusMenu::ItemInvoked, this, &PluginsItem::invokedMenuItem);
    connect(menuInter, &DBusMenu::MenuUnregistered, this, &PluginsItem::requestRefershWindowVisible);
    connect(menuInter, &DBusMenu::MenuUnregistered, menuInter, &DBusMenu::deleteLater, Qt::QueuedConnection);

    menuInter->ShowMenu(QString(QJsonDocument(menuObject).toJson()));
    hidePopup();
}

const QPoint PluginsItem::popupMarkPoint()
{
    QPoint p;
    QWidget *w = this;
    do {
        p += w->pos();
        w = qobject_cast<QWidget *>(w->parent());
    } while (w);

    const QRect r = rect();
    const int offset = 4;
    p += QPoint(r.width() / 2, r.height() + offset);

    return p;
}

void PluginsItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
        return showContextMenu();

    QWidget::mousePressEvent(event);
}

void PluginsItem::hidePopup()
{

}
