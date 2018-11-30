#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include "interfaces/pluginsiteminterface.h"
#include "datetimewidget.h"

#include <QLabel>

namespace dtb {
namespace widgets {
class SwitchItem;
}
namespace datetime {

class DateTimePlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
public:
    DateTimePlugin(QWidget *parent = 0);
    ~DateTimePlugin();

    struct MenuModel {
        bool is24;
        QString format;

        void setModel(const QJsonObject &obj) {
            is24 = obj["Is24"].toBool();
            format = obj["Format"].toString();
        }

        const QJsonObject value() {
            QJsonObject obj;

            obj["Is24"] = is24;
            obj["Format"] = format;

            return obj;
        }
    };

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;

    QWidget* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

    void setDefaultColor(PluginProxyInterface::DefaultColor color) Q_DECL_OVERRIDE;

private slots:
    void saveConfig();
    void invokedMenuItem(QAction *);

private:
    PluginProxyInterface *m_proxyInter;
    Plugin::DateTime::DateTimeWidget *m_centralWidget;
    MenuModel m_settings;
    QMenu *m_menu;
    widgets::SwitchItem *m_switchItem;
};
}
}

#endif // TIMEWIDGET_H
