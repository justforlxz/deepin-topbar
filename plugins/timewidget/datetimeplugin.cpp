#include "datetimeplugin.h"

DateTimePlugin::DateTimePlugin(QWidget *parent)
    : QObject(parent)
{
    m_centralWidget = new DateTimeWidget;
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

    return m_centralWidget->popupWidget();
}

const QString DateTimePlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return QString("dde-datetime");
}
