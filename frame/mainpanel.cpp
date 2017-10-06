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
//    loadModule(new systemtray::SystemTrayPlugin);

    loadModule(new media::MediaControlPlugin);

    loadModule(new power::PowerPlugin);

    loadModule(new sound::SoundPlugin);

    loadModule(new network::NetworkPlugin);

    loadModule(new systeminfo::SystemInfoPlugin);

    loadModule(new account::AccountPlugin);

    loadModule(new datetime::DateTimePlugin);

    loadModule(new notify::NotifyPlugin);
}

void MainPanel::loadModule(PluginsItemInterface * const module)
{
    // init
    module->init(this);

    PluginsItem *item = new PluginsItem(module, "");

    m_mainLayout->addWidget(item);
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

bool MainPanel::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

//    QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

//    if (!keyEvent)
//        return false;

//    if (event->type() == QEvent::KeyRelease)

    return false;
}
