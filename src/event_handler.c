#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_event.h>
#include "signal_handler.h"
#include "utils.h"
#include "clock.h"
#include "graphics.h"
#include "window_state.h"
#include "event_handler.h"

void handle_property_notify(xcb_generic_event_t *event)
{
    xcb_property_notify_event_t *property_notify_event =
        (xcb_property_notify_event_t *) event;

    uint8_t list_stacking_changed = 
        property_notify_event->atom == 
        config->ewmh_connection->_NET_CLIENT_LIST_STACKING;

    if (list_stacking_changed)
        set_window_visibility();
}

void handle_expose()
{
    set_font_graphics_context("fixed");

    if (user_settings->show_time)
        draw_date_time(user_settings->time_format, -6);

    if (user_settings->show_date)
        draw_date_time(user_settings->date_format, 6);

    xcb_free_gc(config->connection, g_config->graphics_context);
}

void handle_generic_event(xcb_generic_event_t *event)
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
}

void event_loop()
{
    xcb_generic_event_t *event;

    while ((event = xcb_wait_for_event(config->connection)))
    {
        handle_generic_event(event);

        free(event);

        if (!config->keep_running)
            break;
    }
}
