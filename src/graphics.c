#include "graphics.h"
#include "error_handler.h"
#include "utils.h"
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

    for(; depth_iter.rem; xcb_depth_next (&depth_iter))
        if(depth_iter.data->depth == 32)
            g_config->visual = xcb_depth_visuals_iterator(depth_iter.data).data;

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
            colormap, config->screen->root, 
            g_config->visual->visual_id);

    uint32_t mask = 
        XCB_CW_BACK_PIXEL | 
        XCB_CW_BORDER_PIXEL | 
        XCB_CW_OVERRIDE_REDIRECT | 
        XCB_CW_COLORMAP;

    uint32_t values[4] = { 
        0x00990000, 
        0, 
        1, 
        colormap 
    };

    xcb_create_window(
            config->connection,
            32,
            g_config->window,
            config->screen->root,
            10, 10,
            80, 50,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            g_config->visual->visual_id,
            mask,
            values);

    set_window_visibility();
}


