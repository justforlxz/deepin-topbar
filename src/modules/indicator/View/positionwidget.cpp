/*
 * Copyright (C) 2017 ~ 2017 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
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

#include "positionwidget.h"

#include <QDesktopServices>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QSignalMapper>
#include <QUrl>

#if 0
QT_TRANSLATE_NOOP("PositionWidget", "Home")
QT_TRANSLATE_NOOP("PositionWidget", "Desktop")
QT_TRANSLATE_NOOP("PositionWidget", "Document")
QT_TRANSLATE_NOOP("PositionWidget", "Photo")
QT_TRANSLATE_NOOP("PositionWidget", "Video")
#endif

using namespace dtb;
using namespace dtb::indicator;

PositionWidget::PositionWidget(QWidget *parent) : ContentModule(parent)
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);

    QLabel *posLbl = new QLabel(tr("Position"));
    posLbl->setStyleSheet("color: white;");

    layout->addWidget(posLbl, 0, Qt::AlignLeft | Qt::AlignVCenter);

    setLayout(layout);

    m_menu = new QMenu(this);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    QMap<QString, QStandardPaths::StandardLocation> actionMap{
        { "Home", QStandardPaths::HomeLocation },
        { "Desktop", QStandardPaths::DesktopLocation },
        { "Document", QStandardPaths::DocumentsLocation },
        { "Photo", QStandardPaths::PicturesLocation },
        { "Video", QStandardPaths::MoviesLocation }
    };

    for (auto it = actionMap.constBegin(); it != actionMap.constEnd(); ++it) {
        QAction *action = new QAction(tr(it.key().toStdString().c_str()), this);
        signalMapper->setMapping(action, it.value());
        m_menu->addAction(action);
        connect(action, &QAction::triggered, signalMapper,
                static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    }

    connect(
        signalMapper,
        static_cast<void (QSignalMapper::*)(const int)>(&QSignalMapper::mapped),
        this, &PositionWidget::handleAction);

    setStyleSheet("QLabel {color: black;}");
}

void PositionWidget::handleAction(const int &action)
{
    QDesktopServices::openUrl(
        QUrl(QStandardPaths::standardLocations(
                 static_cast<QStandardPaths::StandardLocation>(action))
                 .first()));

    emit requestHidePopupWindow();
}
