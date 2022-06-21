#ifndef UTILS_H
#define UTILS_H

#include "prototypes.h"

extern xcb_config_t *config;
extern xcb_graphics_config_t *g_config;
extern settings_t *user_settings;

void cleanup();
void set_window_visibility();
xcb_window_t get_active_window();
void set_window_name(char* wm_name);
void set_window_class(char* wm_class);
point_t center_text_in_window(char *text);
void set_font_graphics_context(char *font_name);

#endif
