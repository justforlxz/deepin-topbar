#include "mainframe.h"
#include "frame.h"
#include "frameshadow.h"
#include <DApplication>
#include <QDebug>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setTheme("light");

    if (a.setSingleInstance("deepin-topbar")) {
        a.setApplicationName("deepin-topbar");
        a.setApplicationVersion("0.2");

        QFont font = a.font();
        font.setFamily("Noto Sans CJK SC");
        a.setFont(font);

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
