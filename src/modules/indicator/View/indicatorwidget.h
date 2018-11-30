#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include "frame/item/contentmodule.h"
#include "entry.h"
#include <QWidget>

#include <com_deepin_daemon_systeminfo.h>
#include <com_deepin_dde_daemon_dock.h>
#include <com_deepin_dde_daemon_dock_entry.h>

using Systeminfo = com::deepin::daemon::SystemInfo;
using DockInter = com::deepin::dde::daemon::Dock;
using DockEntry = com::deepin::dde::daemon::dock::Entry;

namespace dtb {
namespace indicator {
class IndicatorWidget : public ContentModule
{
    Q_OBJECT
public:
    explicit IndicatorWidget(QWidget *parent = nullptr);
    ~IndicatorWidget();
    void initUI();

signals:
    void requestBackgroundChanged(const QColor &color);

public slots:
    void forceQuit();

private slots:
    void getAllEntry();
    void addEntry(const QDBusObjectPath &entryPath, const int index);
    void removeEntry(const QString &entryID);
    void refreshActiveWindow();

private:
    DockInter *m_dockInter;
    QList<DockEntry *> m_entryList;
    Entry *m_entry;
    DockEntry *m_activeWindow;
    Systeminfo *m_systeminfo;
    QString m_systemVersion;
};
}
}

#endif // INDICATORWIDGET_H
