#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_event.h>
#include "config.h"
#include "event_handler.h"
#include "error_handler.h"
#include "graphics.h"
#include "utils.h"

void event_loop(xcb_config_t *config)
{
    xcb_generic_event_t *event;

    while ((event = xcb_wait_for_event(config->connection)))
    {
        switch (event->response_type & XCB_EVENT_RESPONSE_TYPE_MASK)
        {
        case XCB_EXPOSE:
            handle_expose(config);
            break;

        case XCB_PROPERTY_NOTIFY:
            handle_property_notify(config, event);
            break;

        default:
            break;
        }

        free(event);
    }
}

int main()
{
    xcb_config_t config;
    xcb_graphics_config_t g_config;

    initialize(&config);
    initialize_graphics(&config, &g_config);

    create_window(&config, &g_config);
    hide_taskbar_icon(&config);

    event_loop(&config);

    disconnect(&config);

    return EXIT_SUCCESS;
}
