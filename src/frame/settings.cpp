#include "settings.h"
#include <qsettingbackend.h>

#include <QStandardPaths>
#include <QApplication>
#include <QDebug>

using namespace dtb;

static Settings * _settings = nullptr;

Settings &Settings::InStance()
{
    if (!_settings) {
        _settings = new Settings;
    }

    return *_settings;
}

Settings::Settings(QObject *parent)
    : QObject(parent)
{
    m_configPath = QString("%1/%2/%3/config.conf")
            .arg(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation))
            .arg(qApp->organizationName())
            .arg(qApp->applicationName());
    qDebug() << "configPath" << m_configPath;
    auto backend = new DTK_CORE_NAMESPACE::QSettingBackend(m_configPath);

    m_settings = DTK_CORE_NAMESPACE::DSettings::fromJsonFile(":/settings.json");
    m_settings->setBackend(backend);

    connect(m_settings, &DTK_CORE_NAMESPACE::DSettings::valueChanged, this, &Settings::valueChanged);
}
