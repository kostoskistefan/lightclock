#include "utils.h"
#include "graphics.h"
#include "prototypes.h"
#include "event_handler.h"
#include "error_handler.h"
#include "initialization.h"
#include "signal_handler.h"

xcb_config_t *config;
xcb_graphics_config_t *g_config;
settings_t *user_settings;

int main()
{
    config = malloc(sizeof(xcb_config_t));
    g_config = malloc(sizeof(xcb_graphics_config_t));
    user_settings = malloc(sizeof(settings_t));

    initialize_lightclock();

    create_window();

    set_sigint_signal();

    set_timer();

    event_loop();

    cleanup();

    return EXIT_SUCCESS;
}
