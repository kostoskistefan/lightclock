#include <stdio.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_icccm.h>
#include "utils.h"
#include "graphics.h"
#include "window_state.h"
#include "error_handler.h"

xcb_window_t get_active_window()
{
    xcb_get_input_focus_cookie_t cookie =
        xcb_get_input_focus(config->connection);

    xcb_generic_error_t *error = NULL;

    xcb_get_input_focus_reply_t *reply =
        xcb_get_input_focus_reply(config->connection, cookie, &error);

    if (error)
        exit_with_error_message("Failed to get active window");

    xcb_window_t active_window = reply->focus;

    free(reply);

    return active_window;
}

void set_window_name(char *wm_name)
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

void set_window_class(char *wm_class)
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
    if (get_active_window_fullscreen_state())
        xcb_map_window_checked(config->connection, g_config->window);

    else
        xcb_unmap_window_checked(config->connection, g_config->window);

    invalidate();
}

void cleanup()
{
    printf("\n");

    xcb_ewmh_connection_wipe(config->ewmh_connection);
    free(config->ewmh_connection);

    xcb_flush(config->connection);
    xcb_disconnect(config->connection);

    free(user_settings);
    free(g_config);
    free(config);
}

xcb_font_t get_font(char *font_name)
{
    xcb_font_t font = xcb_generate_id(config->connection);

    xcb_void_cookie_t font_cookie = xcb_open_font_checked(
        config->connection,
        font,
        strlen(font_name),
        font_name);

    check_cookie_error(font_cookie, "Failed to open font");

    return font;
}

xcb_gcontext_t create_graphics_context(xcb_font_t font)
{
    xcb_gcontext_t graphics_context = xcb_generate_id(config->connection);

    uint32_t mask = 
        XCB_GC_FOREGROUND |
        XCB_GC_BACKGROUND |
        XCB_GC_FONT;

    uint32_t values[3] = {
        user_settings->foreground_color,
        user_settings->background_color,
        font
    };

    xcb_void_cookie_t graphics_context_cookie =
        xcb_create_gc_checked(
            config->connection,
            graphics_context,
            g_config->window,
            mask,
            values);

    check_cookie_error(
        graphics_context_cookie,
        "Failed to create graphics context");

    return graphics_context;
}

void set_font_graphics_context(char *font_name)
{
    xcb_font_t font = get_font(font_name);
    xcb_gcontext_t graphics_context = create_graphics_context(font);

    g_config->graphics_context = graphics_context;

    xcb_close_font(config->connection, font);
}

point_t center_text_in_window(char *text)
{
    point_t coordinates;

    uint8_t length = strlen(text);

    uint32_t text_width = length * 5 + length;

    coordinates.x = (CLOCK_WINDOW_WIDTH - text_width) / 2;
    coordinates.y = CLOCK_WINDOW_HEIGHT / 2 + 5;

    return coordinates;
}
