#include "indicatorplugin.h"

using namespace dtb;
using namespace dtb::indicator;

IndicatorPlugin::IndicatorPlugin(QObject *parent) : QObject(parent)
{
    m_centralWidget = new IndicatorWidget;
}

const QString IndicatorPlugin::pluginName() const
{
    return QString("indicator");
}

void IndicatorPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *IndicatorPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_centralWidget;
}
