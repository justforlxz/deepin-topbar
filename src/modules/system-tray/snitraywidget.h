/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     listenerri <listenerri@gmail.com>
 *
 * Maintainer: listenerri <listenerri@gmail.com>
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

#ifndef SNITRAYWIDGET_H
#define SNITRAYWIDGET_H

#include "abstracttraywidget.h"
#include "dbus/sni/statusnotifieritem_interface.h"

#include <dbusmenu-qt5/dbusmenuimporter.h>

#include <QMenu>
#include <QDBusObjectPath>

using namespace com::deepin::dde;

enum ItemCategory {UnknownCategory = -1, ApplicationStatus, Communications, SystemServices, Hardware};
enum ItemStatus {UnknownStatus = -1, Passive, Active, NeedsAttention};
enum IconType {UnknownIconType = -1, Icon, OverlayIcon, AttentionIcon, AttentionMovieIcon};

class SNITrayWidget : public AbstractTrayWidget
{
    Q_OBJECT
public:
    SNITrayWidget(const QString &sniServicePath, QWidget *parent = Q_NULLPTR);
    virtual ~SNITrayWidget();

    void setActive(const bool active) Q_DECL_OVERRIDE;
    void updateIcon() Q_DECL_OVERRIDE;
    void sendClick(uint8_t mouseButton, int x, int y) Q_DECL_OVERRIDE;
    const QImage trayImage() Q_DECL_OVERRIDE;

    bool isValid();

    static QString toSNIKey(const QString &sniServicePath) { return QString("sni:%1").arg(sniServicePath); }
    static bool isSNIKey(const QString &itemKey) { return itemKey.startsWith("sni:"); }
    static QString toSNIServicePath(QString itemKey) { return itemKey.remove("sni:"); }

private Q_SLOTS:
    void refreshIcon();
    void refreshOverlayIcon();
    void refreshAttentionIcon();

private:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    QPair<QString, QString> serviceAndPath(const QString &servicePath);
    QPixmap newIconPixmap(IconType iconType);

private:
    StatusNotifierItem *m_sniInter;

    DBusMenuImporter *m_dbusMenuImporter;

    QMenu *m_menu;
    QTimer *m_updateTimer;

    QPixmap m_pixmap;
    QPixmap m_overlayPixmap;
};

#endif /* SNIWIDGET_H */
