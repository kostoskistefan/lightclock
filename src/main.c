#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb_event.h>
#include "prototypes.h"
#include "utils.h"
#include "config.h"
#include "graphics.h"
#include "event_handler.h"
#include "error_handler.h"

xcb_config_t *config;
xcb_graphics_config_t *g_config;

void event_loop()
{
    xcb_generic_event_t *event;

    while (config->keep_running)
    {
        event = xcb_poll_for_event(config->connection);

        if (event)
        {
            switch (event->response_type & XCB_EVENT_RESPONSE_TYPE_MASK)
            {
                case XCB_EXPOSE:
                    handle_expose();
                    break;

                case XCB_PROPERTY_NOTIFY:
                    handle_property_notify(event);
                    break;

                default:
                    break;
            }

            free(event);
        }
    }
}

int main()
{
    config = malloc(sizeof(xcb_config_t));
    g_config = malloc(sizeof(xcb_graphics_config_t));

    initialize();
    initialize_graphics();

    create_window();
    hide_taskbar_icon();

    event_loop();

    cleanup();

    free(g_config);
    free(config);

    return EXIT_SUCCESS;
}
