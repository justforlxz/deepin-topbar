#include "soundplugin.h"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundPlugin::SoundPlugin()
{
}

const QString SoundPlugin::pluginName() const
{
    return "sound";
}

void SoundPlugin::init(PluginProxyInterface *proxyInter)
{
    m_soundItem = new SoundItem;

    m_menu = new QMenu;

    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");
}

QWidget *SoundPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_soundItem;
}

QMenu *SoundPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_menu;
}
