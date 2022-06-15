#include "utils.h"
#include <stdint.h>
#include <string.h>
#include <xcb/xproto.h>

void retrieve_active_window()
{
    xcb_get_input_focus_cookie_t cookie =
        xcb_get_input_focus(config->connection);

    xcb_get_input_focus_reply_t *reply =
        xcb_get_input_focus_reply(config->connection, cookie, NULL);

    config->active_window = reply->focus;

    free(reply);
}

void get_atom_by_name(char *atom_name, xcb_atom_t output_atom)
{
    xcb_intern_atom_cookie_t cookie =
        xcb_intern_atom(config->connection, 1, strlen(atom_name), atom_name);

    xcb_intern_atom_reply_t *reply =
        xcb_intern_atom_reply(config->connection, cookie, NULL);

    output_atom = reply->atom;

    free(reply);
}

void set_window_atom(xcb_window_t window, xcb_atom_t atom)
{
    xcb_change_property(
        config->connection,
        XCB_PROP_MODE_REPLACE,
        window,
        atom,
        XCB_ATOM_ATOM,
        32,
        1,
        &atom);

    xcb_map_window(config->connection, window);
}

void hide_taskbar_icon()
{
    xcb_atom_t skip_taskbar_atom;

    get_atom_by_name("_NET_WM_STATE_SKIP_TASKBAR", skip_taskbar_atom);
    set_window_atom(config->active_window, skip_taskbar_atom);
}

void cleanup()
{
    xcb_ewmh_connection_wipe(config->ewmh_connection);
    free(config->ewmh_connection);
    xcb_flush(config->connection);
    xcb_disconnect(config->connection);
}
