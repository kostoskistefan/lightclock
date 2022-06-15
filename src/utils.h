#ifndef UTILS_H
#define UTILS_H

#include "prototypes.h"

extern xcb_config_t *config;

void cleanup();
void setup_exit_signal();
void hide_taskbar_icon();
void retrieve_active_window();
void get_atom_by_name(char *atom_name, xcb_atom_t output_atom);
void set_window_atom(xcb_window_t window, xcb_atom_t atom);

#endif
