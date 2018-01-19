#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <DMainWindow>

DWIDGET_USE_NAMESPACE

class SettingsWindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // SETTINGSWINDOW_H
