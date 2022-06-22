#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "prototypes.h"

extern xcb_config_t *config;
extern settings_t *user_settings;

void event_loop();
void handle_expose();

#endif
