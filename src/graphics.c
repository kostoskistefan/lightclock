#include "graphics.h"
#include "error_handler.h"
#include "utils.h"
#include "window_state.h"
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>

void initialize_graphics()
{
    g_config->window = xcb_generate_id(config->connection);
    g_config->visual = NULL;
}

void retrieve_screen_visual()
{
    xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(config->screen);

    if(!depth_iter.data)
        exit_with_error_message("Failed to acquire allowed screen depths");

    while (depth_iter.rem)
    {
        if(depth_iter.data->depth == 32)
            g_config->visual = xcb_depth_visuals_iterator(depth_iter.data).data;

        xcb_depth_next (&depth_iter);
    }

    if (!g_config->visual)
        exit_with_error_message("Failed to get visual");
}

void create_window()
{
    retrieve_screen_visual();

    xcb_colormap_t colormap = xcb_generate_id(config->connection);

    xcb_create_colormap(
            config->connection, 
            XCB_COLORMAP_ALLOC_NONE, 
            colormap, 
            config->screen->root, 
            g_config->visual->visual_id);

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
            g_config->visual->visual_id,
            mask,
            values);

    set_window_name("Lightclock");
    set_window_class("lightclock");
    set_window_visibility();
}

void set_font_graphics_context(char *font_name)
{
    xcb_font_t font = xcb_generate_id(config->connection);

    xcb_void_cookie_t font_cookie = xcb_open_font_checked(
            config->connection, 
            font, 
            strlen(font_name), 
            font_name);

    check_cookie_error(font_cookie, "Failed to open font");

    xcb_gcontext_t graphics_context = xcb_generate_id(config->connection);

    uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_FONT;

    uint32_t values[2] = { 
        config->screen->white_pixel,
        font 
    };

    xcb_void_cookie_t graphics_context_cookie = xcb_create_gc_checked(
            config->connection, 
            graphics_context, 
            g_config->window, 
            mask, 
            values);

    check_cookie_error(
            graphics_context_cookie, 
            "Failed to create graphics context");

    font_cookie = xcb_close_font(config->connection, font);

    g_config->graphics_context = graphics_context;
}
