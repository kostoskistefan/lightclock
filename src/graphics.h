#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "prototypes.h"

extern xcb_config_t *config;
extern xcb_graphics_config_t * g_config;

typedef struct xcb_wm_hints_t
{
    uint32_t flags;
    uint32_t functions;
    uint32_t decorations;
    int32_t input_mode;
    uint32_t status;
} xcb_wm_hints_t;

void initialize_graphics();
void create_window();

#endif
