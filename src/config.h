#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include "error_handler.h"

typedef struct xcb_config_t
{
    int screen_number;
    xcb_connection_t* connection;
    xcb_ewmh_connection_t* ewmh_connection;
    xcb_screen_t* screen;
    xcb_window_t active_window;
} xcb_config_t;

void initialize(xcb_config_t *config);
void disconnect(xcb_config_t *config);

#endif
