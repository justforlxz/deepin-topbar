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

#include "notifydelegate.h"
#include "notifymodel.h"

#include <QPainter>
#include <dimagebutton.h>

DWIDGET_USE_NAMESPACE

NotifyDelegate::NotifyDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
}

void NotifyDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (!index.isValid()) {
        return;
    }

    const QString &strId = index.data(NotifyModel::NotifyIdRole).toString();

    if (strId.isEmpty()) {
        return;
    }

//    const QString &strName = index.data(NotifyModel::NotifyNameRole).toString();
    const QString &strSum = index.data(NotifyModel::NotifySummaryRole).toString();
    const QString &strBody = index.data(NotifyModel::NotifyBodyRole).toString();
    const QString &strIcon = index.data(NotifyModel::NotifyIconRole).toString();
    const QString &strTime = notifyTime(index.data(NotifyModel::NotifyTimeRole).toString());
    bool isRemove = index.data(NotifyModel::NotifyRemoveRole).toBool();
    bool isHover = index.data(NotifyModel::NotifyHoverRole).toBool();
    int xOffset = index.data(NotifyModel::NotifyXOffsetRole).toInt();

    QRect mRect = option.rect;

    // for remove anim
    if (isRemove) {
        mRect.setX(mRect.x() + xOffset);
    }

    QFont timeFont = painter->font();
    timeFont.setPixelSize(10);
    QFontMetrics timeFM(timeFont);
    int timeWidth = timeFM.boundingRect(strTime).width();
    int timeHeight = timeFM.boundingRect(strTime).height();

    if (isHover) {
        // draw hover background
        painter->fillRect(mRect, QColor(254, 254, 254, 0.13 * 255));
    } else {
        // draw time
        QRect timeRect = QRect(mRect.x() + option.rect.width() - timeWidth - 10, mRect.y() + 10,
                               timeWidth, timeHeight);
        painter->setFont(timeFont);
        painter->drawText(timeRect, strTime);
    }
    // draw icon
    QRect iconRect = QRect(mRect.x() + 10, mRect.y() + ((mRect.height() - IconSize.height()) / 2),
                           IconSize.width(), IconSize.height());
    QPixmap pix;
    QString iconUrl;

    if (!strIcon.isEmpty()) {
        const QUrl url(strIcon);
        iconUrl = url.isLocalFile() ? url.toLocalFile() : url.url();
    }

    if (!iconUrl.isEmpty()) {
        pix = notifyPixmap(iconUrl, painter->device());
    } else {
        pix = notifyPixmap(CacheFolder + strId + ".png", painter->device());
    }

    painter->drawPixmap(iconRect, pix);

    // draw summary
    QFont sumFont = painter->font();
    sumFont.setPixelSize(11);

    QFontMetrics sumFM(sumFont);

    QRect sumRect = option.rect;
    sumRect.setLeft(iconRect.right() + 5);
    sumRect.setTop(mRect.top() + 10);
    sumRect.setRight(option.rect.right() - timeWidth - 40);
    sumRect.setHeight(sumFM.height() * 1.2);

    if (!strBody.isEmpty()) {
        const QString &newStrSum = sumFM.elidedText(strSum, Qt::ElideRight, sumRect.width());

        painter->setFont(sumFont);
        painter->drawText(sumRect, newStrSum);
    }

    // draw body
    QFont bodyFont = painter->font();
    bodyFont.setPixelSize(13);

    QRect bodyRect = option.rect;
    bodyRect.setLeft(sumRect.left());
    bodyRect.setRight(sumRect.right());
    bodyRect.setTop(sumRect.bottom() + 5);
    bodyRect.setBottom(option.rect.bottom() - 5);
    painter->setFont(bodyFont);
    const auto bodyElided = holdTextInRect(painter->fontMetrics(), strBody.isEmpty() ? strSum : strBody, bodyRect);

    painter->drawText(bodyRect, bodyElided.first);
}

QWidget *NotifyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    const QString &strId = index.data(NotifyModel::NotifyIdRole).toString();

    if (strId.isEmpty()) {
        return nullptr;
    }

    // view class will delete these object later
    DImageButton *removeBtn = new DImageButton(":/images/notify_close_normal.svg",
                             ":/images/notify_close_hover.svg",
                             ":/images/notify_close_press.svg", parent);
    removeBtn->setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    connect(removeBtn, &DImageButton::clicked, this, &NotifyDelegate::removeBtnClicked);
    return removeBtn;
}

void NotifyDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    DImageButton *mEditor = static_cast<DImageButton *>(editor);
    mEditor->setFixedSize(QPixmap(mEditor->getNormalPic()).size() + QSize(20, 20));
    QRect mRect = option.rect;
    editor->setGeometry(mRect.x() + mRect.width() - mEditor->width(), mRect.y(),
                        mEditor->width(), mEditor->height());
}

QPixmap NotifyDelegate::notifyPixmap(const QString &name, QPaintDevice *device) const
{
    const QIcon &icon = QIcon::fromTheme(name, QIcon::fromTheme("application-x-desktop"));

    if (!icon.isNull()) {
        const qreal ratio = device->devicePixelRatioF();
        QPixmap pixmap = icon.pixmap(IconSize * ratio)
                .scaled(IconSize * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        pixmap.setDevicePixelRatio(ratio);
        return pixmap;
    }

    return QPixmap();
}

QString NotifyDelegate::notifyTime(const QString &t) const
{
    const qlonglong time = t.toLongLong();
    const QDateTime date = QDateTime::fromMSecsSinceEpoch(time);

    if (QDateTime::currentMSecsSinceEpoch() > time) {

        const QString hour = date.toString("hh:mm");

        const uint year = date.date().year();
        uint now = QDateTime::currentDateTime().date().year();

        if (now > year)
            return date.toString("yyyy/MM/dd hh:mm");
        else {
            const uint notify_day = date.date().day();
            now = QDateTime::currentDateTime().date().day();

            const uint month = date.date().month();
            const uint now_month = QDateTime::currentDateTime().date().month();

            if (now_month == month) {

                //contrast day
                const uint time = now - notify_day;

                switch (time) {
                case 0:
                    return hour;
                    break;
                case 1:
                    return tr("Yesterday") + " " + hour;
                    break;
                case 2:
                    return tr("The day before yesterday") + " " + hour;
                    break;
                default:
                    if (time > 7) {
                        return date.toString("MM/dd hh:mm");
                    } else {
                        return tr("%n day(s) ago", "", time) + " " + hour;
                    }
                    break;
                }
            } else {
                return date.toString("MM/dd hh:mm");
            }
        }
    } else {
        return date.toString("yyyy/MM/dd hh:mm");
    }

    return t;
}

const QPair<QString, bool> NotifyDelegate::holdTextInRect(const QFontMetrics &fm, const QString &text, const QRect &rect) const
{
    const int textFlag = Qt::AlignTop | Qt::AlignLeft | Qt::TextWordWrap;
    QPair<QString, QRect> cache(text, rect);

    for (auto it = m_textCache.cbegin(); it != m_textCache.cend(); ++it) {
        if (it->first == cache) {
            return it->second;
        }
    }

    if (rect.contains(fm.boundingRect(rect, textFlag, text))) {
        QPair<QString, bool> result(text, true);
        QPair<QPair<QString, QRect>, QPair<QString, bool>> pair;
        pair.first = cache;
        pair.second = result;
        m_textCache << pair;
        return result;
    }

    QString str(text + "...");

    while (true)
    {
        if (str.size() < 4)
            break;

        QRect boundingRect = fm.boundingRect(rect, textFlag, str);
        if (rect.contains(boundingRect))
            break;

        str.remove(str.size() - 4, 1);
    }

    QPair<QString, bool> result(str, false);
    QPair<QPair<QString, QRect>, QPair<QString, bool>> pair;
    pair.first = cache;
    pair.second = result;
    m_textCache << pair;
    return result;
}
