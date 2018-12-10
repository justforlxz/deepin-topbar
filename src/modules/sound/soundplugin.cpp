#include "soundplugin.h"

using namespace dtb;
using namespace dtb::sound;
using namespace dtb::widgets;

SoundPlugin::SoundPlugin()
{
}

const QString SoundPlugin::pluginName() const
{
    return "Sound";
}

void SoundPlugin::init(PluginProxyInterface *proxyInter)
{
    m_soundItem = new SoundItem;

    m_proxyInter = proxyInter;

    m_proxyInter->addItem(this, "");

    connect(m_soundItem, &SoundItem::requestHidePopupWindow, this, [=] {
        m_proxyInter->hidePopupWindow();
    });
}

QWidget *SoundPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_soundItem;
}

QWidget *SoundPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_soundItem->isSoundItem(QCursor::pos()) ? m_soundItem->menu() : nullptr;
}

void SoundPlugin::setDefaultColor(PluginProxyInterface::DefaultColor color)
{

}
