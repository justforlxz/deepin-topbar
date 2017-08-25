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
        a.setApplicationVersion("0.2");

        // disable scale
        qputenv("QT_SCALE_FACTOR", "1.0");

        QFont font = a.font();
        font.setFamily("Noto Sans CJK SC");
        a.setFont(font);

        MainFrame *mainFrame = new MainFrame;
        mainFrame->show();

        return a.exec();
    }
    return 0;
}
