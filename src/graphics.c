#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include "clock.h"
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
        0, 
        0, 
        1, 
        XCB_EVENT_MASK_EXPOSURE,
        colormap 
    };

    xcb_create_window(
            config->connection,
            32,
            g_config->window,
            config->screen->root,
            1276, 
            708,
            CLOCK_WINDOW_HEIGHT,
            CLOCK_WINDOW_WIDTH, 
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            visual_id,
            mask,
            values);

    set_window_name("Lightclock");
    set_window_class("lightclock");

    set_window_visibility();
}

void draw_time(char *format)
{
    char time[256];

    get_current_date_time(format, time);

    xcb_void_cookie_t text_cookie = xcb_image_text_8_checked(
            config->connection, 
            strlen(time), 
            g_config->window,
            g_config->graphics_context, 
            0, 
            10, 
            time);
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