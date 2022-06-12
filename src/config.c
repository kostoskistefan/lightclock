#include "config.h"

void connect_to_X(xcb_config_t *config)
{
    config->connection = xcb_connect(NULL, &config->screen_number);

    if (xcb_connection_has_error(config->connection))
        exit_with_error_message("Failed to open display");
}

void setup_screen(xcb_config_t *config)
{
    config->screen = NULL;

    config->screen = xcb_setup_roots_iterator(xcb_get_setup(config->connection)).data;

    if (config->screen == NULL)
        exit_with_error_message("Failed to acquire screen");

    config->window = config->screen->root;
}

void initialize_ewmh(xcb_config_t *config)
{
    config->ewmh_connection = (xcb_ewmh_connection_t *) malloc(sizeof(xcb_ewmh_connection_t));

    xcb_intern_atom_cookie_t *ewmh_atoms = 
        xcb_ewmh_init_atoms(config->connection, config->ewmh_connection);

    if (xcb_ewmh_init_atoms_replies(config->ewmh_connection, ewmh_atoms, NULL) == 0)
        exit_with_error_message("Failed to initialize EWMH atoms");
}

void initialize_config(xcb_config_t *config)
{
    connect_to_X(config);
    setup_screen(config);
    initialize_ewmh(config);
}

void setup_event_listening(xcb_config_t *config, char* atom_name)
{
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(
            config->connection, 
            0, 
            strlen(atom_name), 
            atom_name);

    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(
            config->connection, 
            cookie, 
            NULL);

    free(reply);
}

void initialize(xcb_config_t *config)
{
    initialize_config(config);

    uint16_t mask = XCB_CW_EVENT_MASK;
    uint32_t values[1] = { XCB_EVENT_MASK_PROPERTY_CHANGE };

    xcb_change_window_attributes(config->connection, config->screen->root, mask, values);
    setup_event_listening(config, (char *) "_NET_ACTIVE_DESKTOP");
}

void disconnect(xcb_config_t *config)
{
    xcb_ewmh_connection_wipe(config->ewmh_connection);
    free(config->ewmh_connection);
    free(config->screen);
    xcb_flush(config->connection);
    xcb_disconnect(config->connection);
}
