#include "event_handler.h"
#include "graphics.h"
#include "utils.h"

void handle_property_notify(xcb_generic_event_t *event)
{
    xcb_property_notify_event_t *property_notify_event =
        (xcb_property_notify_event_t *)event;

    xcb_atom_t list_stacking_atom =
        config->ewmh_connection->_NET_CLIENT_LIST_STACKING;

    if (property_notify_event->atom == list_stacking_atom)
    {
        retrieve_active_window();

        uint8_t state = get_active_window_fullscreen_state();

        if (g_config->active_window_is_fullscreen != state)
        {
            g_config->active_window_is_fullscreen = state;
            set_window_visibility();
        }
    }
}

void handle_expose()
{
}
