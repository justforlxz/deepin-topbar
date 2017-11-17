#include "mainframe.h"
#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    if (a.setSingleInstance("deepin-topbar")) {
        a.setApplicationName("deepin-topbar");

        MainFrame *mainFrame = new MainFrame;
        mainFrame->show();

        return a.exec();
    }
    return 0;
}
