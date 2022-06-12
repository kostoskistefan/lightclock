#ifndef WINDOW_STATE_H 
#define WINDOW_STATE_H

#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_ewmh.h>
#include "config.h"

void update_focused_window(xcb_config_t *config);
void update_focused_window_state(xcb_config_t *config);

#endif
