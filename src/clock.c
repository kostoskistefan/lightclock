#include "clock.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <xcb/xcb.h>

struct tm get_system_time()
{
    time_t raw_time = time(NULL);
    struct tm * time_info = localtime(&raw_time);

    return *time_info;
}

void get_current_time(char *format, char *output)
{
    struct tm time_info = get_system_time();

    strftime(output, 256, format, &time_info);
}

void get_current_date(char *format)
{

}

void draw_time(char *format)
{
    char time[256];

    get_current_time(format, time);

    xcb_void_cookie_t text_cookie = xcb_image_text_8_checked(
            config->connection, 
            strlen(time), 
            g_config->window,
            g_config->graphics_context, 
            0, 
            10, 
            time);
}
