#include "utils.h"
#include "graphics.h"
#include "event_handler.h"
#include "initialization.h"
#include "signal_handler.h"

xcb_config_t *config;
xcb_graphics_config_t *g_config;

int main()
{
    config = malloc(sizeof(xcb_config_t));
    g_config = malloc(sizeof(xcb_graphics_config_t));

    initialize_lightclock();

    create_window();

    set_sigint_signal();

    set_timer();

    event_loop();

    cleanup();

    return EXIT_SUCCESS;
}
