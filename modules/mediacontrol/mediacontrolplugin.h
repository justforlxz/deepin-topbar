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

    int itemSortKey(const QString &itemKey) override;

    QWidget *itemWidget(const QString &itemKey) override;
    QWidget *itemPopupApplet(const QString &itemKey) override;

    const QString itemCommand(const QString &itemKey) override;

private:
    PluginProxyInterface *m_proxyInter;
    MediaControlWidget *m_centralWidget;
};
}
}


#endif // MEDIACONTROLPLUGIN_H
