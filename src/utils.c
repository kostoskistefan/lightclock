#include "utils.h"
#include "config.h"
#include "graphics.h"
#include "window_state.h"
#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_icccm.h>

void retrieve_active_window()
{
    xcb_get_input_focus_cookie_t cookie =
        xcb_get_input_focus(config->connection);

    xcb_get_input_focus_reply_t *reply =
        xcb_get_input_focus_reply(config->connection, cookie, NULL);

    config->active_window = reply->focus;

    free(reply);
}

void set_window_name(char* wm_name)
{
    xcb_icccm_set_wm_name(
            config->connection,
            g_config->window, 
            XCB_ATOM_STRING, 
            8, 
            strlen(wm_name), 
            wm_name);

    xcb_flush(config->connection);
}

void set_window_class(char* wm_class)
{
    xcb_icccm_set_wm_class(
            config->connection, 
            g_config->window, 
            strlen(wm_class), 
            wm_class);

    xcb_flush(config->connection);
}

void set_window_visibility()
{
    if (get_active_window_fullscreen_state())
    {
        xcb_map_window(config->connection, g_config->window);
        invalidate();
    }

    else 
        xcb_unmap_window(config->connection, g_config->window);
        
    xcb_flush(config->connection);
}

void invalidate()
{
    xcb_expose_event_t event = {
        .response_type = XCB_EXPOSE,
        .window = g_config->window
    };

    xcb_send_event(
            config->connection, 
            0, 
            g_config->window, 
            XCB_EVENT_MASK_EXPOSURE, 
            (char *) &event);

    xcb_flush(config->connection);
}

void cleanup()
{
    xcb_ewmh_connection_wipe(config->ewmh_connection);
    free(config->ewmh_connection);
    xcb_flush(config->connection);
    xcb_disconnect(config->connection);
    free(g_config);
    free(config);
}
