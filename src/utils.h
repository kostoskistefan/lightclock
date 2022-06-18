#ifndef UTILS_H
#define UTILS_H

#include "prototypes.h"

extern xcb_config_t *config;
extern xcb_graphics_config_t *g_config;

void cleanup();
void retrieve_active_window();
void set_window_name(char* wm_name);
void set_window_class(char* wm_class);
void set_window_visibility();
void invalidate();

#endif
