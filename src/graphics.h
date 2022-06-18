#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "prototypes.h"

#define CLOCK_WINDOW_HEIGHT 80
#define CLOCK_WINDOW_WIDTH 50

extern xcb_config_t *config;
extern xcb_graphics_config_t * g_config;

void initialize_graphics();
void create_window();
void set_font_graphics_context(char *font_name);

#endif
