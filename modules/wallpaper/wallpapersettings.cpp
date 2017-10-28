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

#include "wallpapersettings.h"
#include <QListWidgetItem>
#include <QFileDialog>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>

using namespace dtb;
using namespace dtb::wallpaper;

WallpaperSettings::WallpaperSettings(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
    , m_listView(new QListWidget)
{
    m_listView->setViewMode(QListView::ListMode);

    m_layout->setMargin(10);
    m_layout->setSpacing(5);

    QPushButton *addBtn = new QPushButton(tr("Add"));
    QPushButton *removeBtn = new QPushButton(tr("Remove"));
    QPushButton *cleanBtn = new QPushButton(tr("Clean"));
    QPushButton *applyBtn = new QPushButton(tr("Apply"));

    QHBoxLayout *listLayout = new QHBoxLayout;
    listLayout->addWidget(m_listView);

    QVBoxLayout *btnsLayout = new QVBoxLayout;
    btnsLayout->addWidget(addBtn);
    btnsLayout->addWidget(removeBtn);
    btnsLayout->addWidget(cleanBtn);
    btnsLayout->addWidget(applyBtn);

    listLayout->addLayout(btnsLayout);

    m_layout->addLayout(listLayout);

    setLayout(m_layout);

    connect(addBtn, &QPushButton::clicked, this, &WallpaperSettings::addOne);
    connect(removeBtn, &QPushButton::clicked, this, &WallpaperSettings::removeOne);
    connect(cleanBtn, &QPushButton::clicked, this, &WallpaperSettings::clean);
    connect(applyBtn, &QPushButton::clicked, this, &WallpaperSettings::finished);
}

void WallpaperSettings::addOne()
{
    QString file_path = QFileDialog::getExistingDirectory(this, tr("Add Path"), "/home");
    if (file_path.isEmpty())
        return;

    QListWidgetItem *item = new QListWidgetItem;
    item->setText(file_path);

    m_listView->addItem(item);
    m_list << file_path;
}

void WallpaperSettings::removeOne()
{
    const int index = m_listView->currentRow();
    QListWidgetItem *item = m_listView->takeItem(index);
    delete item;

    m_list.removeAt(index);
}

void WallpaperSettings::clean()
{
    for (int i(0); i != m_list.count(); ++i) {
        QListWidgetItem *item = m_listView->takeItem(i);
        delete item;
    }

    m_list.clear();
}

void WallpaperSettings::finished()
{
    QJsonObject obj;
    obj["Folder"] = QJsonArray::fromStringList(m_list);
    obj["Interval"] = 10 * 1000;
    emit requestFinished(obj);
}
