#include "datetimeplugin.h"
#include "datetimepopup.h"

#include <QApplication>
#include <QDesktopWidget>

DateTimePlugin::DateTimePlugin(QWidget *parent)
    : QObject(parent) {
    m_centralWidget = new Plugin::DateTime::DateTimeWidget;
    m_popup = new Plugin::DateTime::DateTimePopup;

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestHide, this, [=] {
        m_proxyInter->requestHidePopup();
    });

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestDateFormat,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestIsCenterChanged,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestIsCenterChanged, this, [=] {
        m_proxyInter->requestHidePopup();
    });

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

    return m_popup;
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

    m_popup->setIsCenter(config["Center"].toBool());

    m_centralWidget->set24HourFormat(config["Is24"].toBool());
    m_popup->setIs24Format(config["Is24"].toBool());

    m_centralWidget->setFormat(config["Format"].toString());
    m_popup->setFormat(config["Format"].toString());

    m_centralWidget->adjustSize();

    if (config["Center"].toBool()) {
        QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
        m_proxyInter->move(pluginName(), (screen.width() - m_centralWidget->width()) / 2, 0);
    } else {
        m_proxyInter->move("");
    }
}

void DateTimePlugin::saveConfig()
{
    QJsonObject object;

    object.insert("Is24", m_popup->is24Format());
    object.insert("Center", m_popup->isCenter());
    object.insert("Format", m_popup->format());
    m_proxyInter->saveConfig(pluginName(), object);

    finished();
}
