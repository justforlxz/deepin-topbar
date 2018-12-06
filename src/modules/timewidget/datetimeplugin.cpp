#include "datetimeplugin.h"
#include "widgets/dwidgetaction.h"
#include "widgets/switchitem.h"

#include <QActionGroup>
#include <QApplication>
#include <QDesktopWidget>

using namespace dtb;
using namespace dtb::datetime;
using namespace dtb::widgets;

DateTimePlugin::DateTimePlugin(QWidget *parent)
    : QObject(parent) {
    m_centralWidget = new Plugin::DateTime::DateTimeWidget;
}

DateTimePlugin::~DateTimePlugin() {

}

const QString DateTimePlugin::pluginName() const {
    return QString("Time");
}

void DateTimePlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, pluginName());
    m_menu = new QMenu(m_centralWidget);
    m_switchItem = new SwitchItem;
    DWidgetAction *switchFormat = new DWidgetAction(m_switchItem);
    m_switchItem->setText(tr("24 Hour Time"));

    m_menu->addAction(switchFormat);
    m_menu->addSeparator();

    QAction *timeSetting = new QAction(tr("Time Settings"), this);
    timeSetting->setData("timeSetting");
    m_menu->addAction(timeSetting);

    connect(m_switchItem, &SwitchItem::clicked, this, [=] (const bool state) {
         m_settings.is24 = state;
         m_centralWidget->set24HourFormat(m_settings.is24);
         m_centralWidget->setFormat(m_settings.format);
         saveConfig();
    });

    connect(m_menu, &QMenu::triggered, this, &DateTimePlugin::invokedMenuItem);

    const QJsonObject obj = m_proxyInter->loadConfig(pluginName());

    m_settings.setModel(obj);

    m_centralWidget->set24HourFormat(m_settings.is24);
    m_centralWidget->setFormat(m_settings.format);
}

QWidget *DateTimePlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *DateTimePlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    if (m_settings.is24) {
        m_switchItem->setCheck(true);
    }
    else {
        m_switchItem->setCheck(false);
    }

    return m_menu;
}

void DateTimePlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}

void DateTimePlugin::invokedMenuItem(QAction *action)
{
    const QString &value = action->data().toString();

    if (value == "timeSetting")
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");

    m_proxyInter->hidePopupWindow();

    saveConfig();
}

void DateTimePlugin::saveConfig()
{
    m_proxyInter->saveConfig(pluginName(), m_settings.value());
}
