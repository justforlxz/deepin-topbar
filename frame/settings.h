#ifndef SETTINGS_H
#define SETTINGS_H

#include <DSettings>
#include <QObject>

namespace dtb {
class Settings : public QObject
{
    Q_OBJECT
public:
    static Settings &InStance();

    inline QPointer<DTK_CORE_NAMESPACE::DSettings> settings() { return m_settings; }

Q_SIGNALS:
    void valueChanged(const QString &key, const QVariant &value);

private:
    Settings(QObject *parent = nullptr);
    QString m_configPath;
    QPointer<DTK_CORE_NAMESPACE::DSettings> m_settings;
};
}

#endif // SETTINGS_H
