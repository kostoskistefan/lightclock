#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <xcb/xcb.h>
#include "config.h"

extern xcb_config_t *config;

void check_cookie_error(xcb_void_cookie_t cookie, char *error_message);
void exit_with_error_message(char *error_message);

#endif
