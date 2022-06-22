#include "initialization.h"
#include "error_handler.h"
#include "graphics.h"
#include "user_settings.h"
#include <xcb/xproto.h>

void connect_to_X()
{
    config->connection = xcb_connect(NULL, NULL);

    if (xcb_connection_has_error(config->connection))
        exit_with_error_message("Failed to open display");
}

void setup_screen()
{
    config->screen =
        xcb_setup_roots_iterator(xcb_get_setup(config->connection)).data;

    if (!config->screen)
        exit_with_error_message("Failed to acquire screen");
}

void initialize_ewmh()
{
    config->ewmh_connection = malloc(sizeof(xcb_ewmh_connection_t));

    xcb_intern_atom_cookie_t *ewmh_atoms =
        xcb_ewmh_init_atoms(config->connection, config->ewmh_connection);

    int ewmh_connection_successful = xcb_ewmh_init_atoms_replies(
        config->ewmh_connection,
        ewmh_atoms,
        NULL);

    if (!ewmh_connection_successful)
        exit_with_error_message("Failed to initialize EWMH atoms");
}

void initialize_xcb_config()
{
    config->keep_running = 1;

    connect_to_X();
    setup_screen();
    initialize_ewmh();
}

void initialize_xcb()
{
    initialize_xcb_config();

    uint32_t mask = XCB_CW_EVENT_MASK;
    uint32_t values[1] = { XCB_EVENT_MASK_PROPERTY_CHANGE };

    xcb_change_window_attributes(
        config->connection,
        config->screen->root,
        mask,
        values);
}

void initialize_graphics()
{
    g_config->window = xcb_generate_id(config->connection);
    intialize_invalidation_event();
}

void initialize_lightclock()
{
    initialize_user_settings();
    initialize_xcb();
    initialize_graphics();
}
