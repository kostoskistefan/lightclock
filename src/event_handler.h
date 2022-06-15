#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <stdio.h>
#include "utils.h"
#include "config.h"
#include "window_state.h"

extern xcb_config_t *config;

void handle_property_notify(xcb_generic_event_t *event);
void handle_expose();

#endif
