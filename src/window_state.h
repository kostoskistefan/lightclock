#ifndef WINDOW_STATE_H 
#define WINDOW_STATE_H

#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include "config.h"

#define WINDOW_STATE_WINDOWED   0
#define WINDOW_STATE_FULLSCREEN 1

uint8_t get_active_window_fullscreen_state(xcb_config_t *config);

#endif
