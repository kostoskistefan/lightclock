#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "prototypes.h"

#define CLOCK_WINDOW_WIDTH 70
#define CLOCK_WINDOW_HEIGHT 30

extern xcb_config_t *config;
extern xcb_graphics_config_t * g_config;
extern settings_t *user_settings;

void invalidate();
void create_window();
void draw_date_time(char *format, int8_t y_offset);

#endif
