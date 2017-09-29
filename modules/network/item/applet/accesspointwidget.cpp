#include "accesspointwidget.h"
#include "horizontalseperator.h"

#include <QHBoxLayout>
#include <QDebug>

DWIDGET_USE_NAMESPACE

using namespace dtb;
using namespace dtb::network;

AccessPointWidget::AccessPointWidget(const AccessPoint &ap)
    : QFrame(nullptr),

      m_activeState(NetworkDevice::Unknow),
      m_ap(ap),
      m_ssidBtn(new QPushButton(this)),
      m_indicator(new DPictureSequenceView(this)),
      m_disconnectBtn(new DImageButton(this)),
      m_securityIcon(new QLabel),
      m_strengthIcon(new QLabel)
{
    m_ssidBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_ssidBtn->setText(ap.ssid());
    m_ssidBtn->setObjectName("Ssid");

    m_disconnectBtn->setVisible(false);
    m_disconnectBtn->setNormalPic(":/wireless/resources/wireless/selected.png");
    m_disconnectBtn->setHoverPic(":/wireless/resources/wireless/disconnect.png");
    m_disconnectBtn->setPressPic(":/wireless/resources/wireless/disconnect_pressed.png");

    QStringList indicatorList;
    for (uint i(1); i != 91; ++i)
        indicatorList << QString(":/wireless/indicator/resources/wireless/spinner14/Spinner%1.png").arg(i, 2, 10, QChar('0'));
    m_indicator->setPictureSequence(indicatorList);
    m_indicator->setFixedSize(14, 14);
    m_indicator->setVisible(false);

    if (ap.secured())
        m_securityIcon->setPixmap(QPixmap(":/wireless/resources/wireless/security.svg"));
    else
    {
        QPixmap pixmap(16, 16);
        pixmap.fill(Qt::transparent);
        m_securityIcon->setPixmap(pixmap);
    }

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->addWidget(m_securityIcon);
    infoLayout->addSpacing(5);
    infoLayout->addWidget(m_strengthIcon);
    infoLayout->addSpacing(10);
    infoLayout->addWidget(m_ssidBtn);
    infoLayout->addWidget(m_indicator);
    infoLayout->addWidget(m_disconnectBtn);
    infoLayout->addSpacing(20);
    infoLayout->setSpacing(0);
    infoLayout->setContentsMargins(15, 0, 0, 0);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addLayout(infoLayout);
    centralLayout->setSpacing(0);
    centralLayout->setMargin(0);

    setStrengthIcon(ap.strength());
    setLayout(centralLayout);
    setStyleSheet("AccessPointWidget #Ssid {"
                  "color:white;"
                  "background-color:transparent;"
                  "border:none;"
                  "text-align:left;"
                  "}"
                  "AccessPointWidget {"
                  "border-radius:4px;"
                  "margin:0 2px;"
                  "border-top:1px solid rgba(255, 255, 255, .05);"
                  "}"
                  "AccessPointWidget:hover {"
                  "border:none;"
                  "margin:0;"
                  "background-color:rgba(255, 255, 255, .1);"
                  "}"
                  "AccessPointWidget[active=true] #Ssid {"
//                  "color:#2ca7f8;"
                  "}");

    connect(m_ssidBtn, &QPushButton::clicked, this, &AccessPointWidget::ssidClicked);
    connect(m_disconnectBtn, &DImageButton::clicked, this, &AccessPointWidget::disconnectBtnClicked);
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
    m_disconnectBtn->setNormalPic(":/wireless/resources/wireless/disconnect.png");
}

void AccessPointWidget::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
    m_disconnectBtn->setNormalPic(":/wireless/resources/wireless/selected.png");
}

void AccessPointWidget::setStrengthIcon(const int strength)
{
    if (strength == 100)
        return m_strengthIcon->setPixmap(QPixmap(":/wireless/resources/wireless/wireless-8-symbolic.svg"));

    m_strengthIcon->setPixmap(QPixmap(QString(":/wireless/resources/wireless/wireless-%1-symbolic.svg").arg(strength / 10 & ~0x1)));
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
