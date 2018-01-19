#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <DMainWindow>
#include "mainpanel.h"

DWIDGET_USE_NAMESPACE

namespace dtb {
    class SettingsWindow : public DMainWindow
    {
        Q_OBJECT
    public:
        explicit SettingsWindow(MainPanel *mainPanel, QWidget *parent = nullptr);

    signals:

    public slots:

    private slots:
        void initUI();

    private:
        MainPanel *m_mainPanel;
        QVBoxLayout *m_layout;
    };
}

#endif // SETTINGSWINDOW_H
