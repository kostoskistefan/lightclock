#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdint.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

typedef struct xcb_config_t
{
    int screen_number;
    uint8_t keep_running;
    xcb_connection_t* connection;
    xcb_ewmh_connection_t* ewmh_connection;
    xcb_screen_t* screen;
    xcb_window_t active_window;
} xcb_config_t;

typedef struct xcb_graphics_config_t 
{
    xcb_window_t window;
    xcb_visualtype_t *visual;
} xcb_graphics_config_t;

typedef struct xcb_mask_value_t
{
    uint32_t mask;
    uint32_t *values;
} xcb_mask_value_t;

#endif
