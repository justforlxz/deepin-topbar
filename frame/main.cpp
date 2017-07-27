#include "mainframe.h"
#include "frame.h"
#include "frameshadow.h"
#include <DApplication>
#include <QDebug>

#include <QtPlatformHeaders/QXcbWindowFunctions>

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

        // Serious warning: I don't know why the dock type was set,
        // but the purpose was achieved, and the implementation is unclear.
        QXcbWindowFunctions::setWmWindowType(shadowWidget->windowHandle(), QXcbWindowFunctions::Dock);

        MainFrame *mainFrame = new MainFrame;
        mainFrame->setShadowWidget(shadowWidget);
        mainFrame->show();

        QXcbWindowFunctions::setWmWindowType(mainFrame->windowHandle(), QXcbWindowFunctions::Dock);

        return a.exec();
    }
    return 0;
}
