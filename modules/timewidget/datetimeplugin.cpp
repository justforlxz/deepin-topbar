#include "datetimeplugin.h"
#include "datetimepopup.h"
#include <QActionGroup>
#include <QApplication>
#include <QDesktopWidget>

using namespace dtb;
using namespace dtb::datetime;

DateTimePlugin::DateTimePlugin(QWidget *parent)
    : QObject(parent) {
    m_centralWidget = new Plugin::DateTime::DateTimeWidget;
    m_popup = new Plugin::DateTime::DateTimePopup;

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestDateFormat,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestIsCenterChanged,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestFormatChanged,
            this, &DateTimePlugin::saveConfig);
}

DateTimePlugin::~DateTimePlugin() {

}

const QString DateTimePlugin::pluginName() const {
    return QString("datetime");
}

void DateTimePlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

int DateTimePlugin::itemSortKey(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *DateTimePlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *DateTimePlugin::itemPopupApplet(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return nullptr;
}

const QString DateTimePlugin::itemCommand(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return QString("deepin-datetime");
}

void DateTimePlugin::popupShow()
{
}

void DateTimePlugin::popupHide()
{
    m_proxyInter->requestHidePopup();
}

void DateTimePlugin::finished()
{
    const QJsonObject &config = m_proxyInter->loadConfig(pluginName());

    if (config.isEmpty())
        return;

    m_settings.is24 = config["Is24"].toBool();
    m_settings.isCenter = config["Center"].toBool();
    m_settings.format = config["Format"].toString();
    m_centralWidget->setFormat(m_settings.format);
    m_centralWidget->set24HourFormat(m_settings.is24);

    m_centralWidget->adjustSize();

//    if (m_settings.isCenter) {
//        QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
//        m_proxyInter->move(pluginName(), (screen.width() - m_centralWidget->width()) / 2, 0);
//    } else {
//        m_proxyInter->move("");
//    }
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

    QAction *centerPos = new QAction(tr("at Center"), this);
    QAction *defaultPos = new QAction(tr("at Default"), this);

    centerPos->setData("centerPos");
    defaultPos->setData("defaultPos");

    centerPos->setCheckable(true);
    defaultPos->setCheckable(true);

    QActionGroup *posGrp = new QActionGroup(this);
    posGrp->setExclusive(true);
    posGrp->addAction(centerPos);
    posGrp->addAction(defaultPos);

    if (m_settings.isCenter)
        centerPos->setChecked(true);
    else
        defaultPos->setChecked(true);

    QMenu *posMenu = new QMenu(tr("Position"));
    posMenu->addAction(centerPos);
    posMenu->addAction(defaultPos);
    menu->addMenu(posMenu);

    QAction *timeSetting = new QAction(tr("Time Settings"), this);
    timeSetting->setData("timeSetting");
    menu->addAction(timeSetting );

    connect(menu, &QMenu::aboutToHide, menu, &QMenu::deleteLater);
    connect(menu, &QMenu::triggered, this, &DateTimePlugin::invokedMenuItem);

    return menu;
}

void DateTimePlugin::invokedMenuItem(QAction *action)
{
    const QString &value = action->data().toString();

    if (value == "is24" || value == "is12")
        m_settings.is24 = value == "is24";

    if (value == "centerPos" || value == "defaultPos")
        m_settings.isCenter = value == "centerPos";

    if (value == "timeSetting")
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");

    action->deleteLater();

    saveConfig();
}

void DateTimePlugin::saveConfig()
{
    QJsonObject object;

    object.insert("Is24", m_settings.is24);
    object.insert("Center", m_settings.isCenter);
    object.insert("Format", m_settings.format);
    m_proxyInter->saveConfig(pluginName(), object);

    finished();
}
