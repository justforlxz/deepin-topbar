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

#include "searchbutton.h"
#include "widgets/fontlabel.h"
#include "frame/utils/global.h"

#include <QHBoxLayout>
#include <QProcess>

using namespace dtb;
using namespace dtb::search;
using namespace dtb::widgets;

SearchButton::SearchButton(QFrame *parent)
    : ContentModule(parent)
    , m_fileWatcher(new QFileSystemWatcher(this))
{
    QHBoxLayout *layout = new QHBoxLayout;

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setContentsMargins(10, 0, 10, 0);

    FontLabel *label = new FontLabel;
    label->setIcon(QChar(0xE721), FONTSIZE);

    layout->addWidget(label);

    setLayout(layout);

    m_fileWatcher->addPath("/usr/bin/");

    connect(m_fileWatcher, &QFileSystemWatcher::directoryChanged, this, &SearchButton::onDirectoryChanged);

    onDirectoryChanged();
}

void SearchButton::mousePressEvent(QMouseEvent *event)
{
    ContentModule::mousePressEvent(event);

    setStyleSheet("background: #1E90FF;");
}

void SearchButton::mouseReleaseEvent(QMouseEvent *event)
{
    ContentModule::mouseReleaseEvent(event);

    setStyleSheet("background: transparent;");

    QProcess::startDetached("albert");

    QProcess::startDetached("albert", QStringList() << "show");
}

void SearchButton::onDirectoryChanged()
{
    QProcess *process = new QProcess;

    const bool isAlbertValid = process->execute("which", QStringList() << "albert") == 0;

    setVisible(isAlbertValid);
}
