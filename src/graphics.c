#include "graphics.h"
#include "error_handler.h"
#include "utils.h"
#include <xcb/xcb.h>
#include <xcb/xproto.h>

void initialize_graphics(xcb_config_t *config, xcb_graphics_config_t *g_config)
{
    g_config->window = xcb_generate_id(config->connection);
}

void hide_window_decorations(xcb_config_t *config, xcb_graphics_config_t *g_config)
{
    char *atom = "_MOTIF_WM_HINTS";

    xcb_intern_atom_cookie_t cookie = 
        xcb_intern_atom(
                config->connection, 
                0, 
                strlen(atom),
                atom);

    xcb_intern_atom_reply_t *reply = 
        xcb_intern_atom_reply(
                config->connection, 
                cookie,
                NULL);

    xcb_wm_hints_t hints;

    hints.flags = 2;
    hints.functions = 0;
    hints.decorations = 0;
    hints.input_mode = 0;
    hints.status = 0;

    xcb_change_property(
            config->connection,
            XCB_PROP_MODE_REPLACE,
            g_config->window,
            reply->atom,
            reply->atom,
            32,
            sizeof(xcb_wm_hints_t),
            &hints);

    free(reply);
}

xcb_visualtype_t *draw_argb_visual(const xcb_screen_t *s)
{
	xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(s);
	xcb_visualtype_iterator_t visual_iter;

	if(depth_iter.data)
		for(; depth_iter.rem; xcb_depth_next (&depth_iter))
			if(depth_iter.data->depth == 32)
				for(visual_iter = xcb_depth_visuals_iterator(depth_iter.data);
						visual_iter.rem; xcb_visualtype_next (&visual_iter))
					return visual_iter.data;

	return NULL;
}

void create_window(xcb_config_t *config, xcb_graphics_config_t *g_config)
{
    xcb_visualtype_t *visual = draw_argb_visual(config->screen);
	xcb_colormap_t cmap = xcb_generate_id(config->connection);

	if (!visual)
		exit_with_error_message("No visual created");

    xcb_create_colormap(
            config->connection, 
            XCB_COLORMAP_ALLOC_NONE, 
            cmap, config->screen->root, 
            visual->visual_id);

    uint32_t background_color = argb_to_hex(0, 0, 0, 0.2);

    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_BORDER_PIXEL | XCB_CW_OVERRIDE_REDIRECT | XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
    uint32_t values[5] = { background_color, 0x00000000, 1, XCB_EVENT_MASK_BUTTON_PRESS, cmap };
 
    xcb_create_window(
            config->connection,
            32,
            g_config->window,
            config->screen->root,
            10, 10,
            150, 100,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            visual->visual_id,
            mask,
            values);

    hide_window_decorations(config, g_config);

    xcb_map_window(config->connection, g_config->window);

    xcb_flush(config->connection);
}


