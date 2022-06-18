#ifndef CLOCK_H
#define CLOCK_H

#include "prototypes.h"

extern xcb_config_t *config;
extern xcb_graphics_config_t *g_config;

void draw_time(char *format);
void get_current_date(char *format);

#endif
