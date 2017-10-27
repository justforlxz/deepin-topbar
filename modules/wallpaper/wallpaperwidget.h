#ifndef WallpaperWIDGET_H
#define WallpaperWIDGET_H

#include <QLabel>
#include <QMenu>
#include <DAboutDialog>

DWIDGET_USE_NAMESPACE

namespace dtb {
    namespace wallpaper {
    class WallpaperModel;
    class WallpaperWidget : public QLabel
    {
        Q_OBJECT
    public:
        explicit WallpaperWidget(QWidget *parent = 0);
        void setModel(WallpaperModel *model);

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
        WallpaperModel *m_model;
    };
    }
}

#endif // WallpaperWIDGET_H
