#ifndef MAINPANEL_H
#define MAINPANEL_H

#include "pluginproxyinterface.h"
#include "item/pluginsitem.h"
#include "item/item.h"
#include <QHBoxLayout>
#include <QWidget>

namespace dtb {
class MainPanel : public QWidget, public PluginProxyInterface
{
    Q_OBJECT
public:
    explicit MainPanel(QWidget *parent = nullptr);
    void initUI();
    void initConnect();

    void requestHidePopup() Q_DECL_OVERRIDE;
    bool saveConfig(const QString &itemKey, const QJsonObject &json) Q_DECL_OVERRIDE;
    const QJsonObject loadConfig(const QString &itemKey) Q_DECL_OVERRIDE;

private slots:
    void loadModules();
    void loadModule(PluginsItemInterface * const module);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QHBoxLayout *m_mainLayout;
};
}

#endif // MAINPANEL_H
