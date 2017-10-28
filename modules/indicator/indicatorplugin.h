#ifndef INDICATORPLUGIN_H
#define INDICATORPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "View/indicatorwidget.h"
#include <QLabel>
#include <QObject>

namespace dtb {
namespace indicator {

class  IndicatorPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT

public:
    IndicatorPlugin(QObject *parent = 0);

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;


private:
    PluginProxyInterface *m_proxyInter;
    IndicatorWidget *m_centralWidget;
};
}
}


#endif // INDICATORPLUGIN_H
