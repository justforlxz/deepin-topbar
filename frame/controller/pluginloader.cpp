#include "pluginloader.h"
#include <QDir>
#include <QLibrary>
#include <QApplication>

PluginLoader::PluginLoader(QObject *parent) :
    QThread(parent)
{

}

void PluginLoader::run()
{
#ifdef QT_DEBUG
    const QDir pluginsDir(QApplication::applicationDirPath() + "/plugins");
#else
    const QDir pluginsDir("/usr/lib/deepin-topbar/plugins");
#endif
    const QStringList plugins = pluginsDir.entryList(QDir::Files);

    for (const QString file : plugins)
    {
        if (!QLibrary::isLibrary(file))
            continue;

        emit pluginFounded(pluginsDir.absoluteFilePath(file));

        msleep(500);
    }

    emit finished();
}
