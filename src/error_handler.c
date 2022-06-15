#include "error_handler.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

void exit_with_error_message(char *message)
{
    fprintf(stderr, "%s\n", message);
    cleanup();
    exit(EXIT_FAILURE);
}
