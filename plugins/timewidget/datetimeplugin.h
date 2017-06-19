#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include "../interfaces/pluginsiteminterface.h"
#include "datetimewidget.h"

#include <QLabel>

class DateTimePlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.topbar.PluginsItemInterface" FILE "datetime.json")

public:
    DateTimePlugin(QWidget *parent = 0);
    ~DateTimePlugin();

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemTipsWidget(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;

private:
    PluginProxyInterface *m_proxyInter;
    DateTimeWidget *m_centralWidget;
};

#endif // TIMEWIDGET_H
