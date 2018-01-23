#include "dbusservice.h"

DBusService::DBusService(MainFrame *parent)
    : QDBusAbstractAdaptor(parent)
    , m_mainFrame(parent)
{

}

MainFrame *DBusService::parent() const
{
    return m_mainFrame;
}

void DBusService::ShowSetting()
{
    m_mainFrame->showSetting();
}
