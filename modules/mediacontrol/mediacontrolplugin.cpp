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

    m_proxyInter->addItem(this, "");
}

QWidget *MediaControlPlugin::itemWidget(const QString &itemKey) {
    Q_UNUSED(itemKey);

    return m_centralWidget;
}
