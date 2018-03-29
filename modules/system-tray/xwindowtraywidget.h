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

#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QWidget>
#include <QTimer>

#include "abstracttraywidget.h"

class XWindowTrayWidget : public AbstractTrayWidget
{
    Q_OBJECT

public:
    explicit XWindowTrayWidget(quint32 winId, QWidget *parent = 0);
    ~XWindowTrayWidget();

    void updateIcon() Q_DECL_OVERRIDE;
    void setActive(const bool active) Q_DECL_OVERRIDE;
    const QImage trayImage() Q_DECL_OVERRIDE;
    void sendClick(uint8_t mouseButton, int x, int y) Q_DECL_OVERRIDE;

    static QString toTrayWidgetId(quint32 winId) { return QString("window:%1").arg(winId); }
    static bool isWinIdKey(const QString &itemKey) { return itemKey.startsWith("window:"); }
    static quint32 toWinId(QString itemKey) { return itemKey.remove("window:").toUInt() ; }

private:
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void configContainerPosition();

    void wrapWindow();
    void sendHoverEvent();
//    void hideIcon();
    void refershIconImage();

private slots:
    void setX11PassMouseEvent(const bool pass);
    void setWindowOnTop(const bool top);
    bool isBadWindow();

private:
    bool m_active = false;
    WId m_windowId;
    WId m_containerWid;
    QImage m_image;

    QTimer *m_updateTimer;
    QTimer *m_sendHoverEvent;
};

#endif // TRAYWIDGET_H
