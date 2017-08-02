#include "accountpopupwidget.h"
#include "fontlabel.h"
#include <QVBoxLayout>
#include <QProcess>
#include <QSignalMapper>

AccountPopupWidget::AccountPopupWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 100);

    QVBoxLayout *layout = new QVBoxLayout;

    setLayout(layout);

    QHBoxLayout *powerAction = new QHBoxLayout;

    FontLabel *m_lock = new FontLabel;
    FontLabel *m_logout = new FontLabel;
    FontLabel *m_reboot = new FontLabel;
    FontLabel *m_suspend = new FontLabel;
    FontLabel *m_shutdown = new FontLabel;

    m_lock->setIcon(QChar(0xE1F6), 16);
    m_logout->setIcon(QChar(0xE248), 16);
    m_reboot->setIcon(QChar(0xE1CD), 16);
    m_shutdown->setIcon(QChar(0xE7E8), 16);
    m_suspend->setIcon(QChar(0xE708), 16);

    powerAction->addWidget(m_reboot, 0, Qt::AlignCenter);
    powerAction->addWidget(m_shutdown, 0, Qt::AlignCenter);
    powerAction->addWidget(m_lock, 0, Qt::AlignCenter);
    powerAction->addWidget(m_suspend, 0, Qt::AlignCenter);
    powerAction->addWidget(m_logout, 0, Qt::AlignCenter);

    layout->addLayout(powerAction);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(m_logout, "Logout");
    signalMapper->setMapping(m_suspend, "Suspend");
    signalMapper->setMapping(m_shutdown, "Shutdown");
    signalMapper->setMapping(m_reboot, "Restart");
    connect(signalMapper, static_cast<void (QSignalMapper::*)(const QString &action)>(&QSignalMapper::mapped), this, &AccountPopupWidget::handleShutdownAction);

    connect(m_logout, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_suspend, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_shutdown, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_reboot, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(m_lock, SIGNAL(clicked()), this, SLOT(handleLockAction()));

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

    connect(m_hideAni, &QPropertyAnimation::finished, this, &AccountPopupWidget::requestHidePopup);


    //load Account
}

void AccountPopupWidget::showAni()
{
    m_showAni->start();
}

void AccountPopupWidget::hideAni()
{
    m_hideAni->start();
}

void AccountPopupWidget::handleShutdownAction(const QString &action)
{
    const QString command = QString("dbus-send --print-reply --dest=com.deepin.dde.shutdownFront " \
                                    "/com/deepin/dde/shutdownFront " \
                                    "com.deepin.dde.shutdownFront.%1").arg(action);

    QProcess::startDetached(command);
}

void AccountPopupWidget::handleLockAction()
{
    const QString command = QString("dbus-send --print-reply --dest=com.deepin.dde.lockFront " \
                                    "/com/deepin/dde/lockFront " \
                                    "com.deepin.dde.lockFront.Show");

    QProcess::startDetached(command);
}
