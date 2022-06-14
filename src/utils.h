#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xproto.h>
#include "config.h"

void retrieve_active_window(xcb_config_t *config);
xcb_atom_t get_atom_by_name(xcb_config_t *config, char *atom_name);
void set_window_atom(xcb_config_t *config, xcb_window_t window, xcb_atom_t atom);
void hide_taskbar_icon(xcb_config_t *config);
uint32_t argb_to_hex(uint8_t red, uint8_t green, uint8_t blue, float opacity);

#endif
