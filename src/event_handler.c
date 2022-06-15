#include "event_handler.h"

void handle_property_notify(xcb_generic_event_t *event)
{
    xcb_property_notify_event_t *property_notify_event =
        (xcb_property_notify_event_t *)event;

    xcb_atom_t list_stacking_atom =
        config->ewmh_connection->_NET_CLIENT_LIST_STACKING;

    if (property_notify_event->atom == list_stacking_atom)
    {
        retrieve_active_window();

        uint8_t fullscreen_state = get_active_window_fullscreen_state();

        printf("%d\n", fullscreen_state);
        //config->keep_running = 0;
    }
}

void handle_expose()
{
}
