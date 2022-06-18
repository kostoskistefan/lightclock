#include "error_handler.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void check_cookie_error(xcb_void_cookie_t cookie, char *error_message)
{
    xcb_generic_error_t *error = xcb_request_check(config->connection, cookie);

    if (error)
    {
        fprintf(stderr, "ERROR: %s : %u\n", error_message , error->error_code);
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void exit_with_error_message(char *error_message)
{
    fprintf(stderr, "ERROR: %s\n", error_message);
    cleanup();
    exit(EXIT_FAILURE);
}
