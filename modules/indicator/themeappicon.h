#ifndef THEMEAPPICON_H
#define THEMEAPPICON_H

#include <QObject>

class ThemeAppIcon : public QObject
{
    Q_OBJECT
public:
    explicit ThemeAppIcon(QObject *parent = 0);
    ~ThemeAppIcon();

    static QPixmap getIcon(const QString iconName);
};

#endif // THEMEAPPICON_H
