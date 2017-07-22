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
            m_centralWidget, &Plugin::DateTime::DateTimeWidget::set24HourFormat);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestDateFormat,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestIsCenterChanged,
            this, &DateTimePlugin::saveConfig);

    connect(m_popup, &Plugin::DateTime::DateTimePopup::requestIsCenterChanged, this, [=] {
        m_proxyInter->requestHidePopup();
    });
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

    if (config["Center"].toBool()) {
        QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());
        m_proxyInter->move(pluginName(), (screen.width() - m_centralWidget->width()) / 2, 0);
    } else {
        m_proxyInter->move("");
    }

    m_popup->setIsCenter(config["Center"].toBool());

    m_centralWidget->set24HourFormat(config["Format"].toBool());
    m_popup->setIs24Format(config["Format"].toBool());
}

void DateTimePlugin::saveConfig()
{
    QJsonObject object;

    object.insert("Format", m_popup->is24Format());
    object.insert("Center", m_popup->isCenter());

    m_proxyInter->saveConfig(pluginName(), object);

    finished();
}
