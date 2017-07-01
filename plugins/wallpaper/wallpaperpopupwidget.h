#ifndef WallpaperPOPUPWIDGET_H
#define WallpaperPOPUPWIDGET_H

#include <QWidget>
#include <QPropertyAnimation>

class WallpaperPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WallpaperPopupWidget(QWidget *parent = 0);

signals:
    void requestHidePopup() const;

public slots:
    void showAni();
    void hideAni();

private:
    QPropertyAnimation *m_showAni;
    QPropertyAnimation *m_hideAni;
};

#endif // WallpaperPOPUPWIDGET_H
