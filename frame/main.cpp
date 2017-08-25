#include "mainframe.h"
#include <DApplication>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QtX11Extras/QX11Info>

DWIDGET_USE_NAMESPACE

void register_wm_state(WId winid) {
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[2];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DOCK;
    atoms[1] = m_ewmh_connection._NET_WM_STATE_BELOW;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winid, 1, atoms);

    xcb_ewmh_wm_strut_partial_t strutPartial;
    memset(&strutPartial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    // clear strut partial
    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winid, strutPartial);

    // set strct partial
    xcb_ewmh_wm_strut_partial_t strut_partial;
    memset(&strut_partial, 0, sizeof(xcb_ewmh_wm_strut_partial_t));

    strut_partial.top = 28;
    strut_partial.top_start_x = 0;
    strut_partial.top_end_x = 1920;

    xcb_ewmh_set_wm_strut_partial(&m_ewmh_connection, winid, strut_partial);
}

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
        register_wm_state(mainFrame->winId());
        mainFrame->show();

        return a.exec();
    }
    return 0;
}
