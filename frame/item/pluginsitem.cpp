#include "pluginsitem.h"
#include <QEvent>
#include <QHBoxLayout>
#include <QPoint>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>

#include "contentmodule.h"

using namespace dtb;

PluginsItem::PluginsItem(PluginsItemInterface * const pluginInter, const QString &itemKey, QWidget *parent) :
    Item(parent),
    m_pluginInter(pluginInter),
    m_centralWidget(pluginInter->itemWidget(itemKey)),
    m_itemKey(itemKey),
    m_isPressed(false)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_centralWidget, 0, Qt::AlignCenter);
    setLayout(mainLayout);
}

PluginsItem::~PluginsItem()
{
}

const QString PluginsItem::name() const
{
    return m_pluginInter->pluginName();
}

PluginsItemInterface *PluginsItem::itemInter()
{
    return m_pluginInter;
}

void PluginsItem::mousePressEvent(QMouseEvent *event)
{
    Item::mousePressEvent(event);

    showContextMenu();
}

void PluginsItem::paintEvent(QPaintEvent *event)
{
    Item::paintEvent(event);

    if (m_isPressed) {
        QPainter painter(this);
        painter.fillRect(rect(), QColor("#1E90FF"));
    }
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

void PluginsItem::showContextMenu()
{
    QMenu* menu = contextMenu();
    if (!menu)
        return;

    m_isPressed = true;

    update();

    connect(menu, &QMenu::aboutToHide, this, [=] {
        m_isPressed = false;
        update();
    }, Qt::UniqueConnection);

    menu->exec(mapToGlobal(QPoint(pos().x(), height()) - pos()));
}

