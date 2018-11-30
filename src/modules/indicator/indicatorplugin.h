#ifndef INDICATORPLUGIN_H
#define INDICATORPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "View/indicatorwidget.h"
#include "View/systemlogo.h"
#include "View/positionwidget.h"
#include "indicatormodel.h"
#include "indicatorworker.h"
#include <QLabel>
#include <QObject>
#include <DThemeManager>

DWIDGET_USE_NAMESPACE

namespace dtb {
namespace indicator {

class  IndicatorPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT

public:
    IndicatorPlugin(QObject *parent = 0);

    const QString pluginName() const Q_DECL_OVERRIDE;

    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;

    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    IndicatorWidget *m_centralWidget;
    SystemLogo *m_logo;
    IndicatorModel *m_model;
    IndicatorWorker *m_worker;
    DThemeManager *m_themeManager;
    PositionWidget *m_positionLbl;
};
}
}


#endif // INDICATORPLUGIN_H
