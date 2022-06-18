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
    xcb_gc_t graphics_context;
} xcb_graphics_config_t;

typedef struct vector2_t
{
    uint32_t x;
    uint32_t y;
} vector2_t;

#endif
