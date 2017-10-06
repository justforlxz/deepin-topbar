#include "mainpanel.h"
#include "../modules/account/accountplugin.h"
#include "../modules/indicator/indicatorplugin.h"
#include "../modules/mediacontrol/mediacontrolplugin.h"
#include "../modules/network/networkplugin.h"
#include "../modules/power/powerplugin.h"
#include "../modules/sound/soundplugin.h"
#include "../modules/timewidget/datetimeplugin.h"
#include "../modules/system-tray/systemtrayplugin.h"
#include "../modules/systeminfo/systeminfoplugin.h"
#include "../modules/notify/notifyplugin.h"

#include "item/pluginsitem.h"

#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QEvent>

using namespace dtb;

MainPanel::MainPanel(QWidget *parent) : QWidget(parent)
{
    initUI();
    initConnect();

    loadModules();
}

void MainPanel::initUI()
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_mainLayout = new QHBoxLayout;

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(3);
    m_mainLayout->setContentsMargins(5, 0, 5, 1);

    setLayout(m_mainLayout);
}

void MainPanel::initConnect()
{
}

void MainPanel::addItem(PluginsItemInterface * const module, const QString &itemKey)
{
    // check

    if (m_moduleMap.contains(module))
        if (m_moduleMap[module].contains(itemKey))
            return;

    PluginsItem *item = new PluginsItem(module, itemKey);

    m_moduleMap[module][itemKey] = item;

    m_mainLayout->addWidget(item);
}

void MainPanel::removeItem(PluginsItemInterface * const module, const QString &itemKey)
{
    if (!m_moduleMap.contains(module))
        return;

    PluginsItem * item = m_moduleMap[module][itemKey];

    if (!item)
        return;

    m_mainLayout->removeWidget(item);

    m_moduleMap[module].remove(itemKey);

    item->deleteLater();
}

void MainPanel::requestHidePopup()
{

}

bool MainPanel::saveConfig(const QString &itemKey, const QJsonObject &json)
{

}

const QJsonObject MainPanel::loadConfig(const QString &itemKey)
{

}

void MainPanel::loadModules()
{
    // indicator is special
    loadModule(new indicator::IndicatorPlugin);

    //Stretch
    m_mainLayout->addStretch();

    // I think here need system tray module
    loadModule(new systemtray::SystemTrayPlugin);

    loadModule(new media::MediaControlPlugin);

    loadModule(new power::PowerPlugin);

    loadModule(new sound::SoundPlugin);

    loadModule(new network::NetworkPlugin);

    loadModule(new systeminfo::SystemInfoPlugin);

    loadModule(new datetime::DateTimePlugin);

    loadModule(new account::AccountPlugin);

    loadModule(new notify::NotifyPlugin);
}

void MainPanel::loadModule(PluginsItemInterface * const module)
{
    // init
    module->init(this);
}

void MainPanel::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    QPen pen(painter.pen());
    pen.setBrush(QColor(0, 0, 0, .3 * 255));
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(QPoint(0, 27), QPoint(width(), 27));
}
