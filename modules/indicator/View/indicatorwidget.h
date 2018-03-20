#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include "item/contentmodule.h"
#include "entry.h"
#include <QWidget>
#include <dbusdock.h>
#include <dbusdockentry.h>
#include <com_deepin_daemon_systeminfo.h>

using systeminfo = com::deepin::daemon::SystemInfo;

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
    DBusDock *m_dockInter;
    QList<DBusDockEntry *> m_entryList;
    Entry *m_entry;
    DBusDockEntry *m_activeWindow;
    systeminfo *m_systeminfo;
    QString m_systemVersion;
};
}
}

#endif // INDICATORWIDGET_H
