#include "utils.h"
#include "config.h"
#include "graphics.h"
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
    if (!g_config->active_window_is_fullscreen)
        xcb_unmap_window(config->connection, g_config->window);

    else 
        xcb_map_window(config->connection, g_config->window);
        
    xcb_flush(config->connection);
}

void cleanup()
{
    xcb_ewmh_connection_wipe(config->ewmh_connection);
    free(config->ewmh_connection);
    xcb_flush(config->connection);
    xcb_disconnect(config->connection);
}

void signal_handler(int signal_type) 
{
    switch(signal_type)
    {
        case SIGINT:
            config->keep_running = 0;
            break;
    }
}

void setup_exit_signal() 
{ 
    struct sigaction signal_action;
    memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_handler = &signal_handler;
    sigaction(SIGINT, &signal_action, NULL);
}
