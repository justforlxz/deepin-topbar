#include "itempopupwindow.h"
#include <QApplication>
#include <QDesktopWidget>

ItemPopupWindow::ItemPopupWindow(QWidget *parent)
    : DBlurEffectWidget(parent)
{
    setBlendMode(DBlurEffectWidget::InWindowBlend);
    setMaskColor(DBlurEffectWidget::LightColor);

    setWindowFlags(Qt::X11BypassWindowManagerHint  | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_InputMethodEnabled, false);

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

    setVisible(true);

    QList< QWidget* > children;
    do {
       children = m_layout->findChildren< QWidget* >();
       if (children.count() == 0)
           break;
       m_layout->removeWidget(children.at(0));
    } while (true);

    m_layout->addWidget(content);
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
