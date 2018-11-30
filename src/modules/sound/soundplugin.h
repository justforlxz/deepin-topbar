#ifndef SoundPLUGIN_H
#define SoundPLUGIN_H

#include "interfaces/pluginsiteminterface.h"
#include "sounditem.h"
#include <QObject>

namespace dtb {
namespace sound {

class SoundPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    SoundPlugin();

    const QString pluginName() const Q_DECL_OVERRIDE;
    void init(PluginProxyInterface *proxyInter) Q_DECL_OVERRIDE;


    QWidget *itemWidget(const QString &itemKey) Q_DECL_OVERRIDE;

    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private:
    PluginProxyInterface *m_proxyInter;
    SoundItem *m_soundItem;
};
}
}

#endif // SoundPLUGIN_H
