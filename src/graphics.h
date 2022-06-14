#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include "config.h"

typedef struct xcb_graphics_config_t 
{
    xcb_window_t window;
    xcb_depth_t *depth;
    xcb_visualtype_t *visual;
} xcb_graphics_config_t;

typedef struct xcb_wm_hints_t
{
    uint32_t flags;
    uint32_t functions;
    uint32_t decorations;
    int32_t input_mode;
    uint32_t status;
} xcb_wm_hints_t;

void initialize_graphics(xcb_config_t *config, xcb_graphics_config_t *g_config);
void create_window(xcb_config_t *config, xcb_graphics_config_t *g_config);

#endif
