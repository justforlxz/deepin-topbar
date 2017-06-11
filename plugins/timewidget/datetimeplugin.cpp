#include "datetimeplugin.h"

DateTimePlugin::DateTimePlugin(QWidget *parent)
    : QObject(parent)
{
    m_centralWidget = new DateTimeWidget;
    m_tips = new QLabel;
}

DateTimePlugin::~DateTimePlugin()
{

}

const QString DateTimePlugin::pluginName() const
{
    return QString("datetime");
}

void DateTimePlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, QString());
}

int DateTimePlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *DateTimePlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *DateTimePlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_tips;
}

const QString DateTimePlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("dde-datetime");
}

const QString DateTimePlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(1);

    QMap<QString, QVariant> settings;
    settings["itemId"] = "settings";
    settings["itemText"] = tr("24 Hour Time");
    settings["isActive"] = true;
    items.push_back(settings);

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
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)
    Q_UNUSED(menuId)

//    if (menuId == "open")
//        QProcess::startDetached("dbus-send --print-reply --dest=com.deepin.dde.ControlCenter /com/deepin/dde/ControlCenter com.deepin.dde.ControlCenter.ShowModule \"string:datetime\"");
//    else
//        m_centralWidget->toggleHourFormat();
}
