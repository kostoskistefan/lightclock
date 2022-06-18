#include "window_state.h"
#include "error_handler.h"
#include "utils.h"
#include <xcb/xcb.h>

xcb_ewmh_get_atoms_reply_t get_active_window_states()
{
    xcb_ewmh_get_atoms_reply_t window_states;

    retrieve_active_window();

    xcb_get_property_cookie_t cookie =
        xcb_ewmh_get_wm_state(config->ewmh_connection, config->active_window);

    uint8_t wm_state_reply_has_error = xcb_ewmh_get_wm_state_reply(
        config->ewmh_connection,
        cookie,
        &window_states,
        NULL);

    if (!wm_state_reply_has_error)
        exit_with_error_message("Failed to get window states");

    return window_states;
}

uint8_t get_active_window_fullscreen_state()
{
    xcb_ewmh_get_atoms_reply_t window_states = get_active_window_states();

    xcb_atom_t fullscreen_atom =
        config->ewmh_connection->_NET_WM_STATE_FULLSCREEN;

    for (uint32_t i = 0; i < window_states.atoms_len; i++)
    {
        uint8_t window_is_fullscreen =
            window_states.atoms[i] == fullscreen_atom;

        if (window_is_fullscreen)
            return WINDOW_STATE_FULLSCREEN;
    }

    xcb_ewmh_get_atoms_reply_wipe(&window_states);

    return WINDOW_STATE_WINDOWED;
}
