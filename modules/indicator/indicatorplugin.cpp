#include "indicatorplugin.h"
#include "../frame/utils/global.h"

using namespace dtb;
using namespace dtb::indicator;

IndicatorPlugin::IndicatorPlugin(QObject *parent)
    : QObject(parent)
    , m_themeManager(DThemeManager::instance())
{
}

const QString IndicatorPlugin::pluginName() const
{
    return QString("indicator");
}

void IndicatorPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_centralWidget = new IndicatorWidget;
    m_logo = new SystemLogo;

    m_model = new IndicatorModel;
    m_worker = new IndicatorWorker(m_model);

    m_logo->setModel(m_model);

    m_model->moveToThread(qApp->thread());
    m_worker->moveToThread(qApp->thread());

    connect(m_logo, &SystemLogo::requestForceQuit, m_centralWidget, &IndicatorWidget::forceQuit);

    m_proxyInter->addItem(this, "Logo");
    m_proxyInter->addItem(this, "Indicator");
}

QWidget *IndicatorPlugin::itemWidget(const QString &itemKey)
{
    if (itemKey == "Logo")
        return m_logo;
    else
        return m_centralWidget;
}

QMenu *IndicatorPlugin::itemContextMenu(const QString &itemKey)
{
    if (itemKey == "Logo")
        return m_logo->menu();

    return nullptr;
}

void IndicatorPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{
    switch (color) {
    case PluginProxyInterface::Light:
        m_themeManager->setTheme(m_logo, "light/theme/light");
        m_themeManager->setTheme(m_centralWidget, "light/theme/light");
        break;
    case PluginProxyInterface::Dark:
        m_themeManager->setTheme(m_logo, "dark/theme/dark");
        m_themeManager->setTheme(m_centralWidget, "dark/theme/dark");
        break;
    default:
        break;
    }
}
