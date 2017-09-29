#ifndef WallpaperWIDGET_H
#define WallpaperWIDGET_H

#include <QLabel>

class WallpaperWidget : public QLabel
{
    Q_OBJECT
public:
    explicit WallpaperWidget(QWidget *parent = 0);
};

#endif // WallpaperWIDGET_H
