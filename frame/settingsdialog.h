#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QFrame>
#include "mainpanel.h"

namespace dtb {
class SettingsDialog : public QFrame {
public:
    explicit SettingsDialog(MainPanel *mainPanel, QWidget *parent = nullptr);

private:
    MainPanel *m_mainPanel;
};
}

#endif // SETTINGSWINDOW_H
