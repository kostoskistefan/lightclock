#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "prototypes.h"

#define CLOCK_WINDOW_WIDTH 50
#define CLOCK_WINDOW_HEIGHT 80

extern xcb_config_t *config;
extern xcb_graphics_config_t * g_config;

void invalidate();
void create_window();
void draw_time(char *format);

#endif
