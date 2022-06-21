#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include "clock.h"
#include "initialization.h"
#include "prototypes.h"
#include "user_settings.h"
#include "utils.h"
#include "graphics.h"
#include "window_state.h"
#include "error_handler.h"

xcb_visualid_t get_screen_visual_id()
{
    xcb_depth_iterator_t depth_iter =
        xcb_screen_allowed_depths_iterator(config->screen);

    if(!depth_iter.data)
        exit_with_error_message("Failed to acquire allowed screen depths");

    while (depth_iter.rem)
    {
        if(depth_iter.data->depth == 32)
            return xcb_depth_visuals_iterator(depth_iter.data).data->visual_id;

        xcb_depth_next(&depth_iter);
    }

    exit_with_error_message("Failed to acquire 32-bit visual");

    return EXIT_FAILURE;
}

xcb_colormap_t create_colormap(xcb_visualid_t visual_id)
{
    xcb_colormap_t colormap = xcb_generate_id(config->connection);

    xcb_create_colormap(
            config->connection, 
            XCB_COLORMAP_ALLOC_NONE, 
            colormap, 
            config->screen->root, 
            visual_id);

    return colormap;
}

void create_window()
{
    xcb_visualid_t visual_id = get_screen_visual_id();
    xcb_colormap_t colormap = create_colormap(visual_id);

    uint32_t mask = 
        XCB_CW_BACK_PIXEL | 
        XCB_CW_BORDER_PIXEL | 
        XCB_CW_OVERRIDE_REDIRECT | 
        XCB_CW_EVENT_MASK |
        XCB_CW_COLORMAP;

    uint32_t values[5] = { 
        user_settings->background_color, 
        0, 
        1, 
        XCB_EVENT_MASK_EXPOSURE,
        colormap 
    };

    point_t coordinates = get_position();

    xcb_create_window(
            config->connection,
            32,
            g_config->window,
            config->screen->root,
            coordinates.x, 
            coordinates.y,
            CLOCK_WINDOW_WIDTH, 
            CLOCK_WINDOW_HEIGHT,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            visual_id,
            mask,
            values);

    set_window_name("Lightclock");
    set_window_class("lightclock");

    set_window_visibility();
}

void draw_string(char *string, point_t coordinates)
{
    xcb_void_cookie_t text_cookie = xcb_image_text_8_checked(
            config->connection, 
            strlen(string), 
            g_config->window,
            g_config->graphics_context, 
            coordinates.x, 
            coordinates.y, 
            string);

    check_cookie_error(text_cookie, "Failed to draw clock on main window");
}

void draw_centered_string(char *string, int8_t y_offset)
{
    point_t coordinates = center_text_in_window(string);

    coordinates.y += y_offset;

    draw_string(string, coordinates);
}

void draw_date_time(char *format, int8_t y_offset)
{
    char time[256];

    get_current_date_time(format, time);

    draw_centered_string(time, y_offset);
}

void invalidate()
{
    xcb_expose_event_t *event = malloc(sizeof(xcb_expose_event_t));

    event->response_type = XCB_EXPOSE;
    event->window = g_config->window;

    xcb_send_event(
            config->connection, 
            0, 
            g_config->window, 
            XCB_EVENT_MASK_EXPOSURE, 
            (char *) event);

    xcb_flush(config->connection);

    free(event);
}
