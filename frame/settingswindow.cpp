#include "settingswindow.h"

#include "utils/global.h"

#include <QVBoxLayout>

using namespace dtb;

SettingsWindow::SettingsWindow(MainPanel *mainPanel, QWidget *parent)
    : DMainWindow(parent)
    , m_mainPanel(mainPanel)
    , m_layout(new QVBoxLayout)
{
    initUI();
}

void SettingsWindow::initUI()
{
    QWidget *content = new QWidget;
    content->setLayout(m_layout);

    setCentralWidget(content);
}
