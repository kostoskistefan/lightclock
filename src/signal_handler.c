#include <time.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include "graphics.h"
#include "signal_handler.h"

void set_timer()
{
    previous_update_time = time(0);
}

void trigger_clock_update()
{
    time_t current_time = time(0);

    if (current_time - previous_update_time == 1)
    {
        previous_update_time = current_time;
        invalidate();
    }
}

void signal_handler(int signal_type) 
{
    if (signal_type == SIGINT)
        config->keep_running = 0;
}

void set_sigint_signal() 
{ 
    struct sigaction signal_action;
    memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_handler = &signal_handler;
    sigaction(SIGINT, &signal_action, NULL);
}

