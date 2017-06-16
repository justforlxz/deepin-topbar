#include "mainframe.h"
#include "frame.h"
#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);

    if (a.setSingleInstance("dde-topbar")) {
        a.setApplicationName("dde-topbar");
        a.setApplicationVersion("1.0");

        Frame *frame = new Frame;
        frame->registerDesktop();
        frame->show();
        frame->lower();

        MainFrame *mainFrame = new MainFrame;
        mainFrame->registerDesktop();
        mainFrame->activateWindow();
        mainFrame->show();

        return a.exec();
    }
    return 0;
}
