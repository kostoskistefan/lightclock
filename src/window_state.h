#ifndef WINDOW_STATE_H 
#define WINDOW_STATE_H

#include "prototypes.h"

#define WINDOW_STATE_WINDOWED   0
#define WINDOW_STATE_FULLSCREEN 1

extern xcb_config_t *config;

uint8_t get_active_window_fullscreen_state();

#endif
