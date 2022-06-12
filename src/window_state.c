#include "window_state.h"

void update_focused_window(xcb_config_t *config)
{
    xcb_get_input_focus_cookie_t cookie = xcb_get_input_focus(config->connection);

    xcb_get_input_focus_reply_t *reply = 
        xcb_get_input_focus_reply(
                config->connection, 
                cookie, 
                NULL);

    config->window = reply->focus;

    free(reply);
}

uint8_t get_focused_window_states(xcb_config_t *config, xcb_ewmh_get_atoms_reply_t *window_states)
{
    xcb_get_property_cookie_t cookie = 
        xcb_ewmh_get_wm_state(config->ewmh_connection, config->window);

    return !xcb_ewmh_get_wm_state_reply(
            config->ewmh_connection, 
            cookie, 
            window_states, 
            NULL);
}

void update_focused_window_state(xcb_config_t *config)
{
    xcb_ewmh_get_atoms_reply_t window_states;

    uint8_t error = get_focused_window_states(config, &window_states);

    if (error)
    {
        config->window_state = ERROR_STATE;
        return;
    }

    for (unsigned int i = 0; i < window_states.atoms_len; i++)
    {
        uint8_t window_is_fullscreen = window_states.atoms[i] == config->ewmh_connection->_NET_WM_STATE_FULLSCREEN;

        if (window_is_fullscreen)
        {
            config->window_state = WINDOW_STATE_FULLSCREEN;
            return;
        }
    }

    xcb_ewmh_get_atoms_reply_wipe(&window_states);

    config->window_state = WINDOW_STATE_WINDOWED;
}
