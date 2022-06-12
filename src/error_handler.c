#include "error_handler.h"

void exit_with_error_message(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}
