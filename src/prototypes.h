#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include <stdint.h>
#include <time.h>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>

typedef struct xcb_config_t
{
    uint8_t keep_running;
    xcb_screen_t* screen;
    xcb_connection_t* connection;
    xcb_ewmh_connection_t* ewmh_connection;
} xcb_config_t;

typedef struct xcb_graphics_config_t 
{
    xcb_window_t window;
    xcb_gc_t graphics_context;
} xcb_graphics_config_t;

typedef struct point_t 
{
    uint32_t x;
    uint32_t y;
} point_t;

enum clock_position {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

typedef struct settings_t
{
    uint8_t show_time;
    uint8_t show_date;
    char time_format[256];
    char date_format[256];
    uint32_t background_color;
    uint32_t foreground_color;
    uint16_t vertical_margin;
    uint16_t horizontal_margin;
    enum clock_position position; 
} settings_t;

#endif
