#include "itempopupwindow.h"

#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>

DWIDGET_USE_NAMESPACE

const int MOUSE_BUTTON(1 << 1);

ItemPopupWindow::ItemPopupWindow(QWidget *parent)
    : DArrowRectangle(ArrowBottom, parent)
{
    m_wmHelper = DWindowManagerHelper::instance();

    compositeChanged();

    setBackgroundColor(DBlurEffectWidget::LightColor);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_InputMethodEnabled, false);

    connect(m_wmHelper, &DWindowManagerHelper::hasCompositeChanged, this, &ItemPopupWindow::compositeChanged);
}

ItemPopupWindow::~ItemPopupWindow()
{
}

void ItemPopupWindow::setContent(QWidget *content)
{
    QWidget *lastWidget = getContent();
    if (lastWidget)
        lastWidget->removeEventFilter(this);
    content->installEventFilter(this);

    setAccessibleName(content->objectName() + "-popup");

    DArrowRectangle::setContent(content);
}

void ItemPopupWindow::show(const QPoint &pos)
{
    show(pos.x(), pos.y());
}

void ItemPopupWindow::show(const int x, const int y)
{
    resizeWithContent();

    move(x, y);
    if (!isVisible())
        QWidget::show();

    update();
}

void ItemPopupWindow::compositeChanged()
{
    if (m_wmHelper->hasComposite())
        setBorderColor(QColor(255, 255, 255, 255 * 0.05));
    else
        setBorderColor(QColor("#2C3238"));
}
