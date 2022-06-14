#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdio.h>
#include "utils.h"
#include "config.h"
#include "window_state.h"

void handle_property_notify(xcb_config_t *config, xcb_generic_event_t *event);

void handle_expose(xcb_config_t *config);

#endif
