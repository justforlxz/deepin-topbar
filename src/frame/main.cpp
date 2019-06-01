
#include <DApplication>

#include "dbusservice.h"
#include "mainframe.h"

DWIDGET_USE_NAMESPACE

static const QString getQssFromFile(const QString &name)
{
#ifdef QT_DEBUG
//    qDebug() << "load qss file: " << name;
#endif

    QString qss;

    QFile f(name);
    if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qss = f.readAll();
        f.close();
    }

    return qss;
}

static const QString getStyleSheetFromDir(QDir dir)
{
    QString ret;

    for (auto name : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        if (name.suffix() == "qss") {
            ret.append(getQssFromFile(name.absoluteFilePath()));
        }
    }

    return ret;
}

static const QString styleSheetFromTheme(const QString &theme)
{
    QStringList moduleList = {
        "frame", "widgets",
    };

    QString ret;

    const QString resources = ":/%1/themes/" + theme;
    for (auto module : moduleList)
    {
        QString dir = resources.arg(module);
        ret.append(getStyleSheetFromDir(dir));
    }

    return ret;
}

static void onThemeChange(const QString &theme)
{
    QString qss;
    qss.append(styleSheetFromTheme("common"));
    qss.append(styleSheetFromTheme(theme));

    qApp->setStyleSheet(qss);
}

int main(int argc, char *argv[])
{
    if (QString(getenv("XDG_CURRENT_DESKTOP")) != QStringLiteral("Deepin")) {
        qDebug() << "I only run the Deepin Desktop!";
        return -1;
    }

    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    if (a.setSingleInstance("deepin-topbar")) {
        a.setApplicationName("deepin-topbar");
        a.setOrganizationName("deepin");

        QTranslator translator;
        translator.load("/usr/share/deepin-topbar/translations/deepin-topbar_" +
                        QLocale::system().name());
        a.installTranslator(&translator);

        a.setTheme("semidark");
        onThemeChange("dark");

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
