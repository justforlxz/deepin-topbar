#include "Widget.h"
#include <DApplication>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    a.setApplicationName("topbar");
    a.setApplicationVersion("1.0");

    Widget w;
    w.show();

    return a.exec();
}
