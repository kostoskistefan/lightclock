#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include "prototypes.h"

extern xcb_config_t *config;
extern settings_t *user_settings;

void initialize_user_settings();
point_t get_position();

#endif
