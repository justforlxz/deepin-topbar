#ifndef PLUGINPROXYINTERFACE_H
#define PLUGINPROXYINTERFACE_H

#include <QtCore>
#include <QJsonObject>

namespace dtb {

class PluginsItemInterface;
class PluginProxyInterface
{
public:
    virtual void requestHidePopup() = 0;

    virtual bool saveConfig(const QString &itemKey, const QJsonObject &json) { Q_UNUSED(itemKey); Q_UNUSED(json); return false;}

    virtual const QJsonObject loadConfig(const QString &itemKey) { Q_UNUSED(itemKey); return QJsonObject();}
};

}
#endif // PLUGINPROXYINTERFACE_H
