#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QThread>

class PluginLoader : public QThread
{
    Q_OBJECT

public:
    explicit PluginLoader(QObject *parent);

signals:
    void finished() const;
    void pluginFounded(const QString &pluginFile) const;

protected:
    void run();
};

#endif // PLUGINLOADER_H
