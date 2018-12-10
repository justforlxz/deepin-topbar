#include "notifyplugin.h"
#include "notifywidget.h"

#include <DHiDPIHelper>
#include <QApplication>

using namespace dtb;
using namespace dtb::notify;

DWIDGET_USE_NAMESPACE

NotifyPlugin::NotifyPlugin()
{
    m_notify = new NotifyWidget;
    m_notify->setFixedSize(360, 720 / qApp->devicePixelRatio());
    m_notifyBtn = new QLabel;
    m_notifyBtn->setPixmap(DHiDPIHelper::loadNxPixmap(":/images/split_press.svg"));
}

const QString NotifyPlugin::pluginName() const
{
    return "Notify";
}

void NotifyPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *NotifyPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_notifyBtn;
}

QWidget *NotifyPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_notify;
}

void NotifyPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{
    Q_UNUSED(color);
}
