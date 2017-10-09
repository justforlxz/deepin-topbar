#include "notifypopupwidget.h"
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QApplication>

using namespace dtb;
using namespace dtb::notify;

NotifyPopupWidget::NotifyPopupWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);

    m_showAni = new QPropertyAnimation(this, "size", this);
    m_showAni->setDuration(300);
    m_showAni->setStartValue(QSize(width(), 30));
    m_showAni->setEndValue(size());
    m_showAni->setEasingCurve(QEasingCurve::InOutCubic);

    m_hideAni = new QPropertyAnimation(this, "size", this);
    m_hideAni->setDuration(300);
    m_hideAni->setStartValue(size());
    m_hideAni->setEndValue(QSize(width(), 30));
    m_hideAni->setEasingCurve(QEasingCurve::InOutCubic);

    connect(m_hideAni, &QPropertyAnimation::finished, this, &NotifyPopupWidget::requestHidePopup);

    QDesktopWidget *desktopWidget = qApp->desktop();
    connect(desktopWidget, &QDesktopWidget::screenCountChanged, this, &NotifyPopupWidget::onScreenChanged);
    connect(desktopWidget, &QDesktopWidget::primaryScreenChanged, this, &NotifyPopupWidget::onScreenChanged);

    onScreenChanged();

    //load notify
}

void NotifyPopupWidget::showAni()
{
    m_showAni->start();
}

void NotifyPopupWidget::hideAni()
{
    m_hideAni->start();
}

void NotifyPopupWidget::onScreenChanged()
{
    QDesktopWidget *desktopWidget = qApp->desktop();
    QRect rect = desktopWidget->screenGeometry(desktopWidget->primaryScreen());

    setFixedSize(360 * devicePixelRatioF(), rect.height() - 28 * devicePixelRatioF());
}
