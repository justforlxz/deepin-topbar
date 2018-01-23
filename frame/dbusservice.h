#ifndef DBUSSERVICE_H
#define DBUSSERVICE_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QDBusAbstractAdaptor>

#include "mainframe.h"

class DBusService : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.deepin.dde.topbar")
public:
    explicit DBusService(MainFrame *parent);

    inline MainFrame *parent() const;

public slots:
    void ShowSetting();

private:
    MainFrame *m_mainFrame;
};

#endif // DBUSSERVICE_H
