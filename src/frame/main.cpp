
#include <DApplication>

#include "dbusservice.h"
#include "mainframe.h"

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    if (QString(getenv("XDG_CURRENT_DESKTOP")) != QStringLiteral("Deepin")) {
        qDebug() << "I only run the Deepin Desktop!";
        return -1;
    }

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    if (a.setSingleInstance("deepin-topbar")) {
        a.setApplicationName("deepin-topbar");
        a.setOrganizationName("deepin");

        QTranslator translator;
        translator.load("/usr/share/deepin-topbar/translations/deepin-topbar_" +
                        QLocale::system().name());
        a.installTranslator(&translator);

        MainFrame *mainFrame = new MainFrame;

        DBusService *dbus = new DBusService(mainFrame);
        Q_UNUSED(dbus);

        QDBusConnection::sessionBus().registerService("com.deepin.dde.topbar");
        QDBusConnection::sessionBus().registerObject("/com/deepin/dde/topbar",
                                                     "com.deepin.dde.topbar", mainFrame);

        return a.exec();
    }
    return 0;
}
