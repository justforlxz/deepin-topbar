#include "soundplugin.h"

SoundPlugin::SoundPlugin()
{
    m_Sound = new SoundWidget;
    m_popupWidget = new SoundPopupWidget;
}

const QString SoundPlugin::pluginName() const
{
    return "sound";
}

void SoundPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;

    m_proxyInter->itemAdded(this, "sound");

    connect(m_popupWidget, &SoundPopupWidget::requestHidePopup, this, [=] {
        m_proxyInter->requestHidePopup();
    });
}

int SoundPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return 0;
}

QWidget *SoundPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_Sound;
}

QWidget *SoundPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return m_popupWidget;
}

const QString SoundPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    return "deepin-sound";
}

void SoundPlugin::popupShow()
{
    m_popupWidget->showAni();
}

void SoundPlugin::popupHide()
{
    m_popupWidget->hideAni();
}
