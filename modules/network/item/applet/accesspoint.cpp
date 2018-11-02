/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "accesspoint.h"

#include <QDebug>
#include <QJsonDocument>

AccessPoint::AccessPoint(const QJsonObject &apInfo)
    : QObject(nullptr)
{
    loadApInfo(apInfo);
}

AccessPoint::AccessPoint(const AccessPoint &ap)
    : QObject(nullptr)
{
    *this = ap;
}

AccessPoint::AccessPoint(const QString &info)
{
    const QJsonDocument doc = QJsonDocument::fromJson(info.toUtf8());
    Q_ASSERT(doc.isObject());
    loadApInfo(doc.object());
}

AccessPoint::AccessPoint()
    : QObject(nullptr),
      m_strength(0),
      m_secured(false),
      m_securedInEap(false)
{
}

bool AccessPoint::operator==(const AccessPoint &ap) const
{
    return m_ssid == ap.ssid();
}

bool AccessPoint::operator>(const AccessPoint &ap) const
{
    return m_strength > ap.m_strength;
}

AccessPoint &AccessPoint::operator=(const AccessPoint &ap)
{
    m_strength = ap.m_strength;
    m_secured = ap.m_secured;
    m_securedInEap = ap.m_securedInEap;
    m_path = ap.m_path;
    m_ssid = ap.m_ssid;

    return *this;
}

const QString AccessPoint::ssid() const
{
    return m_ssid;
}

const QString AccessPoint::path() const
{
    return m_path;
}

int AccessPoint::strength() const
{
    return m_strength;
}

bool AccessPoint::secured() const
{
    return m_secured;
}

void AccessPoint::loadApInfo(const QJsonObject &apInfo)
{
    m_strength = apInfo.value("Strength").toInt();
    m_secured = apInfo.value("Secured").toBool();
    m_securedInEap = apInfo.value("SecuredInEap").toBool();
    m_path = apInfo.value("Path").toString();
    m_ssid = apInfo.value("Ssid").toString();
}
