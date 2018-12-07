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

#include "snitraywidget.h"
#include "frame/utils/themeappicon.h"

#include <QPainter>
#include <QApplication>

#include <xcb/xproto.h>

#define IconSize 16

const QStringList ItemCategoryList {"ApplicationStatus" , "Communications" , "SystemServices", "Hardware"};
const QStringList ItemStatusList {"ApplicationStatus" , "Communications" , "SystemServices", "Hardware"};

SNITrayWidget::SNITrayWidget(const QString &sniServicePath, QWidget *parent)
    : AbstractTrayWidget(parent),
        m_dbusMenuImporter(nullptr),
        m_menu(nullptr),
        m_updateTimer(new QTimer(this))
{
    if (sniServicePath.startsWith("/") || !sniServicePath.contains("/")) {
        return;
    }

    QPair<QString, QString> pair = serviceAndPath(sniServicePath);
    const QString &service = pair.first;
    const QString &path = pair.second;

    m_sniInter = new StatusNotifierItem(service, path, QDBusConnection::sessionBus(), this);

    if (!m_sniInter->isValid()) {
        return;
    }

    const QString &menuPath = m_sniInter->menu().path();
    m_dbusMenuImporter = new DBusMenuImporter(service, menuPath, SYNCHRONOUS, this);
    m_menu = m_dbusMenuImporter->menu();

    m_updateTimer->setInterval(100);
    m_updateTimer->setSingleShot(true);

    connect(m_updateTimer, &QTimer::timeout, this, &SNITrayWidget::refreshIcon);
    connect(m_sniInter, &StatusNotifierItem::NewIcon, m_updateTimer, static_cast<void (QTimer::*) ()>(&QTimer::start));
    connect(m_sniInter, &StatusNotifierItem::NewOverlayIcon, this, &SNITrayWidget::refreshOverlayIcon);
    connect(m_sniInter, &StatusNotifierItem::NewAttentionIcon, this, &SNITrayWidget::refreshAttentionIcon);

    QTimer::singleShot(0, this, &SNITrayWidget::refreshIcon);
}

SNITrayWidget::~SNITrayWidget()
{
}

void SNITrayWidget::setActive(const bool active)
{
}

void SNITrayWidget::updateIcon()
{
    m_updateTimer->start();
}

void SNITrayWidget::sendClick(uint8_t mouseButton, int x, int y)
{
    switch (mouseButton) {
        case XCB_BUTTON_INDEX_1:
            m_sniInter->Activate(x, y);
            break;
        case XCB_BUTTON_INDEX_2:
            m_sniInter->SecondaryActivate(x, y);
            break;
        case XCB_BUTTON_INDEX_3:
            showContextMenu(x, y);
            break;
        default:
            qDebug() << "unknown mouse button key";
        break;
    }
}

const QImage SNITrayWidget::trayImage()
{
    return m_pixmap.toImage();
}

bool SNITrayWidget::isValid()
{
    return m_sniInter->isValid();
}

/*
 *ItemCategory SNITrayWidget::category()
 *{
 *    const QString &category = m_sniInter->category();
 *    if (!ItemCategoryList.contains(category)) {
 *        return UnknownCategory;
 *    }
 *
 *    return static_cast<ItemCategory>(ItemCategoryList.indexOf(category));
 *}
 *
 *ItemStatus SNITrayWidget::status()
 *{
 *    const QString &status = m_sniInter->status();
 *    if (!ItemStatusList.contains(status)) {
 *        return UnknownStatus;
 *    }
 *
 *    return static_cast<ItemStatus>(ItemStatusList.indexOf(status));
 *}
 *
 */

void SNITrayWidget::refreshIcon()
{
    QPixmap pix = newIconPixmap(Icon);
    if (pix.isNull()) {
        return;
    }

    m_pixmap = pix;
    update();
    Q_EMIT iconChanged();
}

void SNITrayWidget::refreshOverlayIcon()
{
    QPixmap pix = newIconPixmap(OverlayIcon);
    if (pix.isNull()) {
        return;
    }

    m_overlayPixmap = pix;
    update();
    Q_EMIT iconChanged();
}

void SNITrayWidget::refreshAttentionIcon()
{
    /* TODO: A new approach may be needed to deal with attentionIcon */
    QPixmap pix = newIconPixmap(AttentionIcon);
    if (pix.isNull()) {
        return;
    }

    m_pixmap = pix;
    update();
    Q_EMIT iconChanged();
}

QSize SNITrayWidget::sizeHint() const
{
    return QSize(26, 26);
}

void SNITrayWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    if (m_pixmap.isNull())
        return;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
#ifdef QT_DEBUG
    //painter.fillRect(rect(), Qt::red);
#endif

    const QPoint p = rect().center() - m_pixmap.rect().center() / m_pixmap.devicePixelRatioF();
    painter.drawPixmap(p, m_pixmap);

    if (!m_overlayPixmap.isNull()) {
        painter.drawPixmap(p, m_overlayPixmap);
    }

    painter.end();
}

QPair<QString, QString> SNITrayWidget::serviceAndPath(const QString &servicePath)
{
    QStringList list = servicePath.split("/");
    QPair<QString, QString> pair;
    pair.first = list.takeFirst();

    for (auto i : list) {
        pair.second.append("/");
        pair.second.append(i);
    }

    return pair;
}

QPixmap SNITrayWidget::newIconPixmap(IconType iconType)
{
    QPixmap pixmap;
    if (iconType == UnknownIconType) {
        return pixmap;
    }

    QString iconName;
    DBusImageList dbusImageList;

    switch (iconType) {
        case Icon:
            iconName = m_sniInter->iconName();
            dbusImageList = m_sniInter->iconPixmap();
            break;
        case OverlayIcon:
            iconName = m_sniInter->overlayIconName();
            dbusImageList = m_sniInter->overlayIconPixmap();
            break;
        case AttentionIcon:
            iconName = m_sniInter->attentionIconName();
            dbusImageList = m_sniInter->attentionIconPixmap();
            break;
        case AttentionMovieIcon:
            iconName = m_sniInter->attentionMovieName();
            break;
        default:
            break;
    }

    do {
        if (!iconName.isEmpty()) {
            pixmap = ThemeAppIcon::getIcon(iconName, IconSize);
            if (!pixmap.isNull()) {
                break;
            }
        }

        const auto ratio = qApp->devicePixelRatio();
        if (!dbusImageList.isEmpty()) {
            for (DBusImage dbusImage : dbusImageList) {
                char *image_data = dbusImage.pixels.data();

                if (QSysInfo::ByteOrder == QSysInfo::LittleEndian) {
                    for (int i = 0; i < dbusImage.pixels.size(); i += 4) {
                        *(qint32*)(image_data + i) = qFromBigEndian(*(qint32*)(image_data + i));
                    }
                }

                QImage image((const uchar*)dbusImage.pixels.constData(), dbusImage.width, dbusImage.height, QImage::Format_ARGB32);
                pixmap = QPixmap::fromImage(image.scaled(IconSize, IconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                pixmap.setDevicePixelRatio(ratio);
                if (!pixmap.isNull()) {
                    break;
                }
            }
        }

        if (pixmap.isNull()) {
            qDebug() << "get icon faild!";
        }
    } while (false);

    return pixmap;
}

void SNITrayWidget::showContextMenu(int x, int y)
{
    // ContextMenu does not work
    if (m_sniInter->menu().path().startsWith("/NO_DBUSMENU")) {
        m_sniInter->ContextMenu(x, y);
    } else {
        m_menu->popup(QPoint(x, y));
    }
}
