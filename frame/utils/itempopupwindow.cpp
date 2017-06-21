#include "itempopupwindow.h"

#include <QRegion>
#include <QScreen>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsOpacityEffect>

DWIDGET_USE_NAMESPACE

const int MOUSE_BUTTON(1 << 1);

ItemPopupWindow::ItemPopupWindow(QWidget *parent)
    : DArrowRectangle(ArrowBottom, parent)
    , m_mouseArea(new XMouseArea("com.deepin.api.XMouseArea", "/com/deepin/api/XMouseArea", QDBusConnection::sessionBus(), this))
{
    m_wmHelper = DWindowManagerHelper::instance();

    compositeChanged();

    setBackgroundColor(DBlurEffectWidget::LightColor);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_InputMethodEnabled, false);

    connect(m_wmHelper, &DWindowManagerHelper::hasCompositeChanged, this, &ItemPopupWindow::compositeChanged);

    QDBusPendingCall call = m_mouseArea->RegisterFullScreen();
    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, watcher] {
        if (watcher->isError()) {
            qWarning() << "error registering mouse area";
        } else {
            QDBusReply<QString> reply = watcher->reply();
            m_key = reply.value();
        }
    });

    connect(m_mouseArea, &__XMouseArea::ButtonPress, this, [this] (int, int x, int y, const QString &key) {
        if (key == m_key && !containsPoint(QPoint(x, y))) {
//            hideAni->start();
            sizeChangeAni_h->start();
        }
    });

    m_effect = new QGraphicsOpacityEffect;
//    DArrowRectangle::setGraphicsEffect(m_effect);
//    setGraphicsEffect(m_effect);

    showAni = new QPropertyAnimation(m_effect, "opacity", this);
    hideAni = new QPropertyAnimation(m_effect, "opacity", this);

    showAni->setDuration(250);
    showAni->setStartValue(0.0);
    showAni->setEndValue(1.0);
    showAni->setEasingCurve(QEasingCurve::InBack);

    hideAni->setDuration(250);
    hideAni->setStartValue(1.0);
    hideAni->setEndValue(0.0);
    hideAni->setEasingCurve(QEasingCurve::OutBack);

    connect(hideAni, &QPropertyAnimation::finished, this, &ItemPopupWindow::hide);

    sizeChangeAni_w = new QPropertyAnimation(this, "size", this);
    sizeChangeAni_h = new QPropertyAnimation(this, "size", this);

    connect(sizeChangeAni_w, &QPropertyAnimation::valueChanged, this, [=] {
            resizeWithContent();
    });

    connect(sizeChangeAni_h, &QPropertyAnimation::finished, this, &ItemPopupWindow::hide);
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

    m_content = lastWidget;
    content->setGraphicsEffect(m_effect);

    sizeChangeAni_w->setDuration(300);
    sizeChangeAni_w->setStartValue(QSize(content->width(), 10));
    sizeChangeAni_w->setEndValue(content->size());
    sizeChangeAni_w->setEasingCurve(QEasingCurve::InOutCubic);

    sizeChangeAni_h->setDuration(250);
    sizeChangeAni_h->setStartValue(content->size());
    sizeChangeAni_h->setEndValue(QSize(content->width(), 10));
    sizeChangeAni_h->setEasingCurve(QEasingCurve::InOutCubic);

    setAccessibleName(content->objectName() + "-popup");

    DArrowRectangle::setContent(content);
}

void ItemPopupWindow::showAnimation()
{
    showAni->start();
}

void ItemPopupWindow::hideAnimation()
{
    hideAni->start();
}

void ItemPopupWindow::show(const QPoint &pos)
{
    show(pos.x(), pos.y());
}

void ItemPopupWindow::show(const int x, const int y)
{
    resizeWithContent();

    move(x, y);

    setVisible(!isVisible());

    if (isVisible()) {
        m_effect->setOpacity(1);
        showAni->start();
        sizeChangeAni_w->start();
    } else {
       hideAni->start();
       sizeChangeAni_h->start();
    }
}

void ItemPopupWindow::compositeChanged()
{
    if (m_wmHelper->hasComposite())
        setBorderColor(QColor(255, 255, 255, 255 * 0.05));
    else
        setBorderColor(QColor("#2C3238"));
}

bool ItemPopupWindow::containsPoint(const QPoint &point) const
{
    QRect screen = QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen());

    QRegion r(screen.x(), 0, screen.width(), 25);
    QRegion re(geometry().x(), geometry().y(), rect().width(), rect().height());

    r += re;
    return r.contains(point);
}

bool ItemPopupWindow::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);

    if (event->type() == QEvent::Resize) {
        DArrowRectangle::resizeWithContent();
    }

    return false;
}

void ItemPopupWindow::showEvent(QShowEvent *event)
{
    DArrowRectangle::showEvent(event);

    QTimer::singleShot(1, this, [&] {
        raise();
        activateWindow();
        setFocus(Qt::ActiveWindowFocusReason);
    });
}
