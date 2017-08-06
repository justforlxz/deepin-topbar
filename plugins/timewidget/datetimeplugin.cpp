#include "datetimeplugin.h"
#include "datetimepopup.h"

#include <QApplication>
#include <QDesktopWidget>

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

    m_proxyInter->itemAdded(this, QString());
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

    if (m_settings.isCenter) {
        QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
        m_proxyInter->move(pluginName(), (screen.width() - m_centralWidget->width()) / 2, 0);
    } else {
        m_proxyInter->move("");
    }
}

QString DateTimePlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(1);

    QMap<QString, QVariant> settings;
    settings["itemId"] = "settings";
    if (m_settings.is24)
        settings["itemText"] = tr("24 Hour Time");
    else
        settings["itemText"] = tr("12 Hour Time");
    settings["isActive"] = true;
    items.push_back(settings);

    QMap<QString, QVariant> center;
    center["itemId"] = "isCenter";
    center["itemText"] = tr("Change position");
    center["isActive"] = true;
    items.push_back(center);

    QMap<QString, QVariant> open;
    open["itemId"] = "open";
    open["itemText"] = tr("Time Settings");
    open["isActive"] = true;
    items.push_back(open);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    return QJsonDocument::fromVariant(menu).toJson();
}

void DateTimePlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    if (menuId == "settings")
        m_settings.is24 = !m_settings.is24;

    if (menuId == "isCenter")
        m_settings.isCenter = !m_settings.isCenter;

    if (menuId == "open")
        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");

    saveConfig();
}

void DateTimePlugin::saveConfig()
{
    QJsonObject object;

    object.insert("Is24", m_settings.is24);
    object.insert("Center", m_settings.isCenter);
    object.insert("Format", m_settings.format);
    m_proxyInter->saveConfig(pluginName(), object);

    qDebug() << object;

    finished();
}
