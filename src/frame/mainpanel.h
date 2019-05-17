#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "interfaces/pluginproxyinterface.h"
#include "item/pluginsitem.h"
#include "item/item.h"
#include <QHBoxLayout>
#include <QWidget>
#include <QGSettings>

namespace dtb {
class Settings;
class MainFrame;
class MainPanel : public QWidget, public PluginProxyInterface
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);
    void initUI();
    void initConnect();

    void addItem(PluginsItemInterface * const module, const QString &itemKey) Q_DECL_OVERRIDE;
    void removeItem(PluginsItemInterface * const module, const QString &itemKey) Q_DECL_OVERRIDE;

    bool saveConfig(const QString &itemKey, const QJsonObject &json) Q_DECL_OVERRIDE;
    const QJsonObject loadConfig(const QString &itemKey) Q_DECL_OVERRIDE;

    void hidePopupWindow() Q_DECL_OVERRIDE;
    void showSettingDialog();

private slots:
    void loadModules();
    void loadModule(PluginsItemInterface * const module);
    void reload();

private:
    QHBoxLayout *m_mainLayout;
    QMap<PluginsItemInterface*, QMap<QString, PluginsItem*>> m_moduleMap;
    QGSettings *m_gsettings;
    bool m_isLight;
    DefaultColor m_defaultColor;
    QStringList m_blackList;
    Settings *m_settings;
};
}

#endif // MAINPANEL_H
