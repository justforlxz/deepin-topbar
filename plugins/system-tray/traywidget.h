#ifndef TRAYWIDGET_H
#define TRAYWIDGET_H

#include <QWidget>
#include <QTimer>

class TrayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrayWidget(quint32 winId, QWidget *parent = 0);
    ~TrayWidget();

    void updateIcon();
    const QImage trayImage();
    void sendClick(uint8_t mouseButton, int x, int y);
    void setActive(const bool active);

signals:
    void iconChanged();

private:
    QSize sizeHint() const;
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void moveEvent(QMoveEvent *e);
    void enterEvent(QEvent *e);
    void configContainerPosition();

    void wrapWindow();
//    void hideIcon();
    void refershIconImage();

private slots:
    void setX11PassMouseEvent(const bool pass);
    void setWindowOnTop(const bool top);
    bool isBadWindow();

private:
    bool m_active = false;
    WId m_windowId;
    WId m_containerWid;
    QImage m_image;

    QTimer *m_updateTimer;
    QTimer *m_ignoreRepeat;
    QPoint m_pressPoint;
};

#endif // TRAYWIDGET_H
