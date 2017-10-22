#ifndef TIMEWIDGET_H
#define TIMEWIDGET_H

#include "../interfaces/pluginsiteminterface.h"
#include "datetimewidget.h"
#include "datetimepopup.h"
#include <QLabel>

namespace dtb {
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
    };

    const QString pluginName() const override;
    void init(PluginProxyInterface *proxyInter) override;

    QWidget *itemWidget(const QString &itemKey) override;

    QMenu* itemContextMenu(const QString &itemKey) Q_DECL_OVERRIDE;

private slots:
    void saveConfig();
    void invokedMenuItem(QAction *);

private:
    PluginProxyInterface *m_proxyInter;
    Plugin::DateTime::DateTimeWidget *m_centralWidget;
    Plugin::DateTime::DateTimePopup *m_popup;
    MenuModel m_settings;
};
}
}

#endif // TIMEWIDGET_H
