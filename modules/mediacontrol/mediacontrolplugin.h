#ifndef MEDIACONTROLPLUGIN_H
#define MEDIACONTROLPLUGIN_H

#include "../interfaces/pluginsiteminterface.h"
#include "View/mediacontrolwidget.h"
#include <QObject>
#include <QLabel>

namespace dtb {
namespace media {

class MediaControlPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    MediaControlPlugin(QObject *parent = 0);
    ~MediaControlPlugin();

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    MediaControlWidget *m_centralWidget;
};
}
}


#endif // MEDIACONTROLPLUGIN_H
