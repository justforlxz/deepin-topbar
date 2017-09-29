#include "mediacontrolplugin.h"

using namespace dtb;
using namespace dtb::media;

MediaControlPlugin::MediaControlPlugin(QObject *parent) : QObject(parent) {
    m_centralWidget = new MediaControlWidget;
}

MediaControlPlugin::~MediaControlPlugin() {

}

const QString MediaControlPlugin::pluginName() const {
    return QString("mediacontrol");
}

void MediaControlPlugin::init(PluginProxyInterface *proxyInter) {
    m_proxyInter = proxyInter;
}

int MediaControlPlugin::itemSortKey(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *MediaControlPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}

QWidget *MediaControlPlugin::itemPopupApplet(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return nullptr;
}

const QString MediaControlPlugin::itemCommand(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return QString("deepin-mediacontrol");
}
