#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_event.h>
#include "config.h"
#include "window_state.h"
#include "error_handler.h"

void handle_property_notify(xcb_config_t *config, xcb_property_notify_event_t *event)
{
    if (event->atom == config->ewmh_connection->_NET_CLIENT_LIST_STACKING)
    {
        update_focused_window(config);
        update_focused_window_state(config);

        if (config->window_state == ERROR_STATE)
            exit_with_error_message("Can't get window state");

        else
            printf("%d\n", config->window_state);
    }
}

void event_loop(xcb_config_t* config)
{
    xcb_generic_event_t* event;

    while ((event = xcb_wait_for_event(config->connection)))
    {
        switch (event->response_type & XCB_EVENT_RESPONSE_TYPE_MASK)
        {
            case XCB_PROPERTY_NOTIFY:
                handle_property_notify(config, (xcb_property_notify_event_t*) event);
                break;
        }

        free(event);
    }
}

int main()
{
    xcb_config_t config;

    initialize(&config); 

    event_loop(&config);

    disconnect(&config);

    return 0;
}
