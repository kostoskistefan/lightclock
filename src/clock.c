#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>
#include "clock.h"

struct tm get_system_time()
{
    time_t raw_time = time(NULL);
    struct tm * time_info = localtime(&raw_time);

    return *time_info;
}

void get_current_date_time(char *format, char *output)
{
    struct tm time_info = get_system_time();

    strftime(output, 256, format, &time_info);
}