#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include "entry.h"
#include <QWidget>
#include <DBus/dbusdock.h>
#include <DBus/dbusdockentry.h>

namespace Plugin {
namespace Indicator {
class IndicatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IndicatorWidget(QWidget *parent = nullptr);
    ~IndicatorWidget();
    void initUI();

private slots:
    void getAllEntry();
    void addEntry(const QDBusObjectPath &entryPath, const int index);
    void removeEntry(const QString &entryID);
    void refreshActiveWindow();

private:
    const QString windowTitle(const WindowDict &infos);

private:
    DBusDock *m_dockInter;
    QList<DBusDockEntry *> m_entryList;
    Entry *m_entry;
    DBusDockEntry *m_activeWindow;
};
}
}

#endif // INDICATORWIDGET_H
