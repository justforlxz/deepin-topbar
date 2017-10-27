#ifndef WallpaperWIDGET_H
#define WallpaperWIDGET_H

#include <QLabel>
#include <QMenu>
#include <DAboutDialog>

DWIDGET_USE_NAMESPACE

class WallpaperWidget : public QLabel
{
    Q_OBJECT
public:
    explicit WallpaperWidget(QWidget *parent = 0);

    enum HandleAction{
        Next,
        Abount,
        Brow,
        Preferences
    };

    QMenu *menu() const;

private:
    void handleAction(const int &action);

private:
    void initUI();
    void initMenu();

private:
    QMenu *m_menu;
    DAboutDialog *m_about;
};

#endif // WallpaperWIDGET_H
