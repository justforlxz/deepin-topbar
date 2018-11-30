#ifndef WallpaperWIDGET_H
#define WallpaperWIDGET_H

#include "frame/item/contentmodule.h"
#include "wallpapersettings.h"
#include <QLabel>
#include <QMenu>
#include <DAboutDialog>

DWIDGET_USE_NAMESPACE

namespace dtb {
    namespace wallpaper {
    class WallpaperModel;
    class WallpaperWidget : public ContentModule
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

    signals:
        void requestSetWallpapers(const QJsonObject &value);

    private:
        void handleAction(const int &action);

    private:
        void initUI();
        void initMenu();
        void initConnect();

    private:
        QMenu *m_menu;
        DAboutDialog *m_about;
        WallpaperModel *m_model;
        WallpaperSettings *m_settings;
    };
    }
}

#endif // WallpaperWIDGET_H
