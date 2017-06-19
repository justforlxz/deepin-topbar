#include "mainframe.h"
#include "frame.h"
#include "frameshadow.h"
#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    if (a.setSingleInstance("dde-topbar")) {
        a.setApplicationName("dde-topbar");
        a.setApplicationVersion("1.0");

        Frame *frame = new Frame;
        frame->registerDesktop();
        frame->show();
        frame->lower();

        FrameShadow *shadowWidget = new FrameShadow;
        shadowWidget->screenChanged();
        shadowWidget->show();

        MainFrame *mainFrame = new MainFrame;
        mainFrame->setShadowWidget(shadowWidget);
        mainFrame->registerDockType();
        mainFrame->activateWindow();
        mainFrame->show();

        return a.exec();
    }
    return 0;
}
