#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include "prototypes.h"

extern xcb_config_t *config;

void set_timer();
void delete_timer();
void set_sigint_signal();

#endif
