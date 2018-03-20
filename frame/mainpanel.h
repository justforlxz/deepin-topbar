#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "pluginproxyinterface.h"
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

    void setDefaultColor(const DefaultColor &defaultColor);
    void setBackground(const QColor &color) Q_DECL_OVERRIDE;
    void moveToCenter(PluginsItemInterface * const module, const QString &itemKey) Q_DECL_OVERRIDE;
    void showSettingDialog();

private slots:
    void loadModules();
    void loadModule(PluginsItemInterface * const module);
    void reload();
    void onBackgroundChanged(const QColor &color);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QHBoxLayout *m_mainLayout;
    QMap<PluginsItemInterface*, QMap<QString, PluginsItem*>> m_moduleMap;
    QGSettings *m_gsettings;
    bool m_isLight;
    DefaultColor m_defaultColor;
    QStringList m_blackList;
    Settings *m_settings;
    QVariantAnimation *m_backgroundAni;
    QColor m_backgroundColor;
};
}

#endif // MAINPANEL_H
