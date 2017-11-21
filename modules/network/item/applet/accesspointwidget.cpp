#include "accesspointwidget.h"
#include "../../../../frame/utils/global.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QEvent>

DWIDGET_USE_NAMESPACE

using namespace dtb;
using namespace dtb::network;
using namespace dtb::widgets;

AccessPointWidget::AccessPointWidget(const AccessPoint &ap)
    : QFrame(nullptr)
    , m_activeState(NetworkDevice::Unknow)
    , m_ap(ap)
    , m_ssidBtn(new QPushButton(this))
    , m_indicator(new DPictureSequenceView(this))
    , m_connectedBtn(new QFrame(this))
    , m_disconnectBtn(new FontLabel)
    , m_securityIcon(new FontLabel)
    , m_strengthIcon(new FontLabel)
{
    setFixedWidth(250);

    m_ssidBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_ssidBtn->setText(ap.ssid());
    m_ssidBtn->setObjectName("Ssid");

    m_connectedBtn->setFixedSize(16, 16);

    m_disconnectBtn->setVisible(false);
    m_disconnectBtn->setFixedSize(16, 16);
    m_disconnectBtn->setIcon(QChar(0xE8FB), FONTSIZE);
    m_disconnectBtn->installEventFilter(this);

    QStringList indicatorList;
    for (uint i(1); i != 91; ++i)
        indicatorList << QString(":/wireless/indicator/resources/wireless/spinner14/Spinner%1.png").arg(i, 2, 10, QChar('0'));
    m_indicator->setPictureSequence(indicatorList);
    m_indicator->setFixedSize(14, 14);
    m_indicator->setVisible(false);

    if (ap.secured())
        m_securityIcon->setIcon(QChar(0xE72E), FONTSIZE);

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->setSpacing(0);
    infoLayout->setMargin(0);

    infoLayout->addSpacing(2);
    infoLayout->addWidget(m_indicator);
    infoLayout->addWidget(m_connectedBtn);
    infoLayout->addWidget(m_disconnectBtn);
    infoLayout->addSpacing(2);
    infoLayout->addWidget(m_ssidBtn);
    infoLayout->addSpacing(10);
    infoLayout->addWidget(m_securityIcon);
    infoLayout->addSpacing(5);
    infoLayout->addWidget(m_strengthIcon);
    infoLayout->addSpacing(5);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(infoLayout);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setStrengthIcon(ap.strength());
    setLayout(centralLayout);
    setStyleSheet("dtb--network--AccessPointWidget #Ssid {"
                  "background-color:transparent;"
                  "border:none;"
                  "text-align:left;"
                  "}"
                  "dtb--network--AccessPointWidget:hover {"
                  "border:none;"
                  "margin:0;"
                  "background-color:rgba(255, 255, 255, .1);"
                  "}"
                  "dtb--network--AccessPointWidget QPushButton {"
                  "color: black;"
                  "}");

    connect(m_ssidBtn, &QPushButton::clicked, this, &AccessPointWidget::ssidClicked);
}

bool AccessPointWidget::active() const
{
    return m_activeState == NetworkDevice::Activated;
}

void AccessPointWidget::setActiveState(const NetworkDevice::NetworkState state)
{
    if (m_activeState == state)
        return;

    m_activeState = state;
    setStyleSheet(styleSheet());

    const bool isActive = active();
    m_disconnectBtn->setVisible(isActive);
    m_connectedBtn->setVisible(!isActive);

    if (!isActive && state > NetworkDevice::Disconnected)
    {
        m_indicator->play();
        m_indicator->setVisible(true);
    } else {
        m_indicator->setVisible(false);
    }
}

void AccessPointWidget::enterEvent(QEvent *e)
{
    QWidget::enterEvent(e);
    m_disconnectBtn->setIcon(QChar(0xE711), FONTSIZE);
    m_ssidBtn->setStyleSheet("color: white;");
    m_disconnectBtn->setStyleSheet("color: white;");
}

void AccessPointWidget::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    m_disconnectBtn->setIcon(QChar(0xE8FB), FONTSIZE);
    m_ssidBtn->setStyleSheet("color: black;");
    m_disconnectBtn->setStyleSheet("color: black;");
}

void AccessPointWidget::setStrengthIcon(const int strength)
{
    if (strength <= 20)
        m_strengthIcon->setIcon(QChar(0xEC37), FONTSIZE);
    else if (strength <= 40)
        m_strengthIcon->setIcon(QChar(0xEC38), FONTSIZE);
    else if (strength <= 60)
        m_strengthIcon->setIcon(QChar(0xEC39), FONTSIZE);
    else if (strength <= 80)
        m_strengthIcon->setIcon(QChar(0xEC3A), FONTSIZE);
    else
        m_strengthIcon->setIcon(QChar(0xEC3B), FONTSIZE);
}

bool AccessPointWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_disconnectBtn) {
        if (event->type() == QEvent::MouseButtonRelease)
            emit disconnectBtnClicked();
    }

    return QFrame::eventFilter(watched, event);
}

void AccessPointWidget::ssidClicked()
{
    if (m_activeState == NetworkDevice::Activated)
        return;

    setActiveState(NetworkDevice::Prepare);
    emit requestActiveAP(QDBusObjectPath(m_ap.path()), m_ap.ssid());
}

void AccessPointWidget::disconnectBtnClicked()
{
    setActiveState(NetworkDevice::Unknow);
    emit requestDeactiveAP(m_ap);
}
