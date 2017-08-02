#include "itempopupwindow.h"
#include <QApplication>
#include <QDesktopWidget>

ItemPopupWindow::ItemPopupWindow(QWidget *parent)
    : DBlurEffectWidget(parent)
    , m_lastWidget(nullptr)
{
    setWindowFlags(Qt::BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setBlendMode(DBlurEffectWidget::InWindowBlend);
    setMaskColor(DBlurEffectWidget::LightColor);

    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_InputMethodEnabled, false);

    m_handle = new DPlatformWindowHandle(this);
    m_handle->setBorderWidth(0);
    m_handle->setWindowRadius(0);
    m_handle->setEnableSystemMove(true);
    m_handle->setEnableSystemResize(true);

    m_moveAni = new QVariantAnimation(this);
    m_moveAni->setDuration(250);

    m_layout = new QHBoxLayout;
    m_layout->setMargin(0);
    m_layout->setSpacing(0);
    setLayout(m_layout);
}

ItemPopupWindow::~ItemPopupWindow()
{
}

void ItemPopupWindow::setContent(QWidget *content)
{
    QWidget *lastWidget = (m_lastWidget == nullptr) ? content : m_lastWidget;
    if (lastWidget)
        lastWidget->removeEventFilter(this);
    content->installEventFilter(this);

    if (m_lastWidget)
        m_lastWidget->hide();

    setVisible(true);

    QList< QWidget* > children;
    do {
       children = m_layout->findChildren< QWidget* >();
       if (children.count() == 0)
           break;
       m_layout->removeWidget(children.at(0));
    } while (true);

    content->show();
    m_layout->addWidget(content, 0, Qt::AlignCenter);
    m_lastWidget = content;

    resize(content->size());
}

void ItemPopupWindow::setRect(const QRect &rect)
{
    m_moveAni->setStartValue(m_point.isNull() ? QPoint(rect.x() - 10, rect.y()) : m_point);
    m_moveAni->setEndValue(QPoint(rect.x(), rect.y()));
    m_point = QPoint(rect.x(), rect.y());

    connect(m_moveAni, &QVariantAnimation::valueChanged, this,  [=] (const QVariant &value) {
        move(value.toPoint().x(), value.toPoint().y());
    });

    m_moveAni->start();
    show();
}

bool ItemPopupWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QEvent::Resize) {
        adjustSize();
    }

    return false;
}

void ItemPopupWindow::resizeEvent(QResizeEvent *event)
{
    DBlurEffectWidget::resizeEvent(event);

    const qreal radius = 5;
    QPainterPath path;
    path.moveTo(rect().topRight() - QPointF(radius, 0));
    path.lineTo(rect().topLeft() + QPointF(radius, 0));
    path.quadTo(rect().topLeft(), rect().topLeft() + QPointF(0, radius));
    path.lineTo(rect().bottomLeft() + QPointF(0, -radius));
    path.quadTo(rect().bottomLeft(), rect().bottomLeft() + QPointF(radius, 0));
    path.lineTo(rect().bottomRight() - QPointF(radius, 0));
    path.quadTo(rect().bottomRight(), rect().bottomRight() + QPointF(0, -radius));
    path.lineTo(rect().topRight() + QPointF(0, radius));
    path.quadTo(rect().topRight(), rect().topRight() + QPointF(-radius, -0));

    m_handle->setClipPath(path);
}
