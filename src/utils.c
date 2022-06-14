#include "utils.h"
#include <stdint.h>

void retrieve_active_window(xcb_config_t *config)
{
    xcb_get_input_focus_cookie_t cookie =
        xcb_get_input_focus(config->connection);

    xcb_get_input_focus_reply_t *reply =
        xcb_get_input_focus_reply(config->connection, cookie, NULL);

    config->active_window = reply->focus;

    free(reply);
}

xcb_atom_t get_atom_by_name(xcb_config_t *config, char *atom_name)
{
    xcb_intern_atom_cookie_t cookie =
        xcb_intern_atom(config->connection, 1, strlen(atom_name), atom_name);

    xcb_intern_atom_reply_t *reply =
        xcb_intern_atom_reply(config->connection, cookie, NULL);

    free(reply);

    return reply->atom;
}

void set_window_atom(xcb_config_t *config, xcb_window_t window, xcb_atom_t atom)
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

void hide_taskbar_icon(xcb_config_t *config)
{
    xcb_atom_t skip_taskbar_atom = get_atom_by_name(config, "_NET_WM_STATE_SKIP_TASKBAR");
    set_window_atom(config, config->active_window, skip_taskbar_atom);
}

uint32_t argb_to_hex(uint8_t red, uint8_t green, uint8_t blue, float opacity)
{
    return (((int)(opacity * 255) & 0xff) << 24) + ((red & 0xff) << 16) + ((green & 0xff) << 8) + (blue & 0xff);
}
