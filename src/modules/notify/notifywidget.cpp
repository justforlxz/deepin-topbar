/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     listenerri <190771752ri@gmail.com>
 *
 * Maintainer: listenerri <190771752ri@gmail.com>
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

#include "notifywidget.h"

#include <QVBoxLayout>

NotifyWidget::NotifyWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainVBLayout = new QVBoxLayout;
    m_clearAllButton = new DImageButton;
    m_notifyView = new NotifyView;
    m_notifyModel = new NotifyModel;
    m_notifyDelegate = new NotifyDelegate;
    m_noNotify = new QLabel(tr("No system notifications"));

    m_clearAllButton->setText(tr("Clear all"));
    m_clearAllButton->setAlignment(Qt::AlignCenter);
    m_clearAllButton->setStyleSheet("background-color: rgba(255, 255, 255, 7.65); padding: 4px 0;");
    m_clearAllButton->setContentsMargins(1, 1, -1, -1);

    m_notifyView->setModel(m_notifyModel);
    m_notifyView->setItemDelegate(m_notifyDelegate);
    m_notifyView->setEditTriggers(QListView::NoEditTriggers);

    m_noNotify->setAlignment(Qt::AlignCenter);
    m_noNotify->setVisible(false);

    mainVBLayout->addWidget(m_clearAllButton);
    mainVBLayout->addWidget(m_notifyView);
    mainVBLayout->addWidget(m_noNotify);

    mainVBLayout->setSpacing(1);
    mainVBLayout->setMargin(0);
    mainVBLayout->setContentsMargins(0, 0, 0, 0);

    setStyleSheet("background-color: rgba(255, 255, 255, 7.65);");
    setContentsMargins(0, 0, 0, 0);
    setLayout(mainVBLayout);

    connect(m_notifyDelegate, &NotifyDelegate::removeBtnClicked, this, &NotifyWidget::onRemoveBtnClicked);
    connect(m_clearAllButton, &DImageButton::clicked, this, &NotifyWidget::showClearAllAnim);
    connect(m_notifyModel, &NotifyModel::removeAnimFinished, m_notifyModel, &NotifyModel::removeNotify);
    connect(m_notifyModel, &NotifyModel::removeAnimFinished, this, &NotifyWidget::onRemoveAnimFinished);
    connect(m_notifyModel, &NotifyModel::clearAllAnimFinished, m_notifyModel, &NotifyModel::clearAllNotify);
    connect(m_notifyModel, &NotifyModel::notifyClearStateChanged, this, &NotifyWidget::onNotifyClearStateChanged);
}

void NotifyWidget::showRemoveAnim(const QModelIndex &index)
{
    m_notifyView->closePersistentEditor(index);
    m_notifyModel->showRemoveAnim(index, m_notifyView->width());
}

void NotifyWidget::showClearAllAnim()
{
    m_notifyModel->showClearAllAnim(m_notifyView->width());
}

void NotifyWidget::onNotifyClearStateChanged(bool isClear)
{
    if (isClear) {
        m_clearAllButton->setVisible(false);
        m_notifyView->setVisible(false);
        m_noNotify->setVisible(true);
    } else {
        m_clearAllButton->setVisible(true);
        m_notifyView->setVisible(true);
        m_noNotify->setVisible(false);
    }
}

void NotifyWidget::onRemoveBtnClicked()
{
    showRemoveAnim(m_notifyView->currentHoverIndex());
}

void NotifyWidget::onRemoveAnimFinished(const QModelIndex &index)
{
    // to avoid the remove button appearing at an has removed notification
    if (m_notifyModel->rowCount(QModelIndex()) <= index.row()) {
        return;
    }
    m_notifyView->openPersistentEditor(m_notifyView->currentHoverIndex());
}
