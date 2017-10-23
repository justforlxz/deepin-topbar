#include "notifypopupwidget.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>

using namespace dtb;
using namespace dtb::notify;

NotifyPopupWidget::NotifyPopupWidget(QWidget *parent) : QWidget(parent)
{
    initUI();

    initConnect();
}

void NotifyPopupWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    // play show animation

}

void NotifyPopupWidget::hideEvent(QHideEvent *event)
{
    QWidget::hideEvent(event);

    // play hide animation
}

void NotifyPopupWidget::onScreenChanged()
{
    QDesktopWidget *desktopWidget = qApp->desktop();
    QRect rect = desktopWidget->screenGeometry(desktopWidget->primaryScreen());

    setFixedSize(360 * devicePixelRatioF(), rect.height() - 28 * devicePixelRatioF());
}

void NotifyPopupWidget::initUI()
{
    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);

    QDesktopWidget *desktopWidget = qApp->desktop();
    connect(desktopWidget, &QDesktopWidget::screenCountChanged, this, &NotifyPopupWidget::onScreenChanged);
    connect(desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &NotifyPopupWidget::onScreenChanged);

    onScreenChanged();

    m_showAni = new QPropertyAnimation(this, "pos", this);

    m_hideAni = new QPropertyAnimation(this, "pos", this);
}

void NotifyPopupWidget::initConnect()
{

}
