#ifndef PLUGINPROXYINTERFACE_H
#define PLUGINPROXYINTERFACE_H

#include <QObject>
#include <QJsonObject>

namespace dtb {

class PluginsItemInterface;
class PluginProxyInterface
{
public:
    enum DefaultColor {
        Light,
        Dark
    };

    virtual void addItem(PluginsItemInterface * const module, const QString &itemKey) = 0;

    virtual void removeItem(PluginsItemInterface * const module, const QString &itemKey) = 0;

    virtual bool saveConfig(const QString &itemKey, const QJsonObject &json) { Q_UNUSED(itemKey); Q_UNUSED(json); return false;}

    virtual const QJsonObject loadConfig(const QString &itemKey) { Q_UNUSED(itemKey); return QJsonObject();}

    virtual void hidePopupWindow() = 0;
};

}
#endif // PLUGINPROXYINTERFACE_H
