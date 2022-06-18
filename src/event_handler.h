#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "prototypes.h"

extern xcb_config_t *config;

void event_loop();
void handle_expose();
void handle_property_notify(xcb_generic_event_t *event);

#endif
