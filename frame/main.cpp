#include "mainframe.h"
#include "frame.h"
#include "frameshadow.h"
#include <DApplication>
#include <QDebug>

#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>
#include <QtPlatformHeaders/QXcbWindowFunctions>

DWIDGET_USE_NAMESPACE

void register_wm_state(WId winid) {
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[2];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DOCK;
    atoms[1] = m_ewmh_connection._NET_WM_STATE_BELOW;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winid, 1, atoms);
}


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
        register_wm_state(shadowWidget->winId());
        shadowWidget->screenChanged();
        shadowWidget->show();

        // Serious warning: I don't know why the dock type was set,
        // but the purpose was achieved, and the implementation is unclear.
        // oh, I see. Qt will set _NET_WM_STATE_BELOW
//        QXcbWindowFunctions::setWmWindowType(shadowWidget->windowHandle(), QXcbWindowFunctions::Dock);

        MainFrame *mainFrame = new MainFrame;
        register_wm_state(mainFrame->winId());
        mainFrame->show();

//        QXcbWindowFunctions::setWmWindowType(mainFrame->windowHandle(), QXcbWindowFunctions::Dock);

        return a.exec();
    }
    return 0;
}
