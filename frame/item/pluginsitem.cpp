#include "pluginsitem.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

using namespace dtb;

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

    setStyleSheet("QLabel {color: rgb(67, 67, 62);background: transparent;}");

    setLayout(mainLayout);
}

PluginsItem::~PluginsItem()
{
}

const QString PluginsItem::name() const
{
    return m_pluginInter->pluginName();
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


PluginsItemInterface *PluginsItem::itemInter()
{
    return m_pluginInter;
}

void PluginsItem::mousePressEvent(QMouseEvent *event)
{
    Item::mousePressEvent(event);

    setStyleSheet("QLabel {color: white;background: #1E90FF;}");

    showContextMenu();
}

QMenu *PluginsItem::contextMenu() const
{
    return m_pluginInter->itemContextMenu(m_itemKey);
}

void PluginsItem::detachPluginWidget()
{
    QWidget *widget = m_pluginInter->itemWidget(m_itemKey);
    if (widget)
        widget->setParent(nullptr);
}

bool PluginsItem::containsPoint(const QPoint &point) const
{
    const qreal ratio = devicePixelRatioF();

    QWidget *w = m_pluginInter->itemWidget(m_itemKey);

    if (!w)
        return false;

    // if click self;
    QRect self(w->mapToGlobal(w->pos()) * ratio,
               w->size() * ratio);

    if (isVisible() && self.contains(point))
        return false;

    QRect s = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
    QRegion screen(s.x(), s.y(), s.width(), 27 * ratio);
    ItemPopupWindow *popup = PopupWindow.get();

    if (screen.contains(point) || popup->geometry().contains(point))
        return true;

    return false;
}

void PluginsItem::showContextMenu()
{
    QMenu* menu = contextMenu();
    if (!menu) {
        setStyleSheet("QLabel {color: rgb(67, 67, 62);background: transparent;}");
        return;
    }

    connect(menu, &QMenu::aboutToHide, this,[=] {
        setStyleSheet("QLabel {color: rgb(67, 67, 62);background: transparent;}");
    });

    menu->exec(QPoint(pos().x(), height()));
}

