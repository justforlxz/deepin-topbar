#include "datetimeplugin.h"

#include <QActionGroup>
#include <QApplication>
#include <QDesktopWidget>

using namespace dtb;
using namespace dtb::datetime;

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
    QTimer::singleShot(1, this, [=] {
        m_proxyInter->moveToCenter(this, pluginName());
    });

    const QJsonObject obj = m_proxyInter->loadConfig(pluginName());

    m_settings.setModel(obj);

    m_centralWidget->set24HourFormat(m_settings.is24);
    m_centralWidget->setFormat(m_settings.format);
}

QWidget *DateTimePlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QMenu *DateTimePlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QMenu *menu = new QMenu;

    QAction *is24 = new QAction(this);
    is24->setText(tr("24 Hour Time"));
    is24->setData("is24");

    QAction *is12 = new QAction(this);
    is12->setText(tr("12 Hour Time"));
    is12->setData("is12");

    QActionGroup *formatGrp = new QActionGroup(this);
    formatGrp->addAction(is12);
    formatGrp->addAction(is24);
    formatGrp->setExclusive(true);

    is12->setCheckable(true);
    is24->setCheckable(true);

    if (m_settings.is24)
        is24->setChecked(true);
    else
        is12->setChecked(true);

    QMenu *timeMenu = new QMenu(tr("Time Format"));
    timeMenu->addAction(is12);
    timeMenu->addAction(is24);
    menu->addMenu(timeMenu);

    QAction *timeSetting = new QAction(tr("Time Settings"), this);
    timeSetting->setData("timeSetting");
    menu->addAction(timeSetting );

    connect(menu, &QMenu::aboutToHide, menu, &QMenu::deleteLater);
    connect(menu, &QMenu::triggered, this, &DateTimePlugin::invokedMenuItem);

    return menu;
}

void DateTimePlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}

void DateTimePlugin::invokedMenuItem(QAction *action)
{
    const QString &value = action->data().toString();

    if (value == "is24" || value == "is12")
        m_settings.is24 = value == "is24";

    m_centralWidget->set24HourFormat(m_settings.is24);

    m_centralWidget->setFormat(m_settings.format);

    if (value == "timeSetting")
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");

    action->deleteLater();

    saveConfig();
}

void DateTimePlugin::saveConfig()
{
    m_proxyInter->saveConfig(pluginName(), m_settings.value());
}
