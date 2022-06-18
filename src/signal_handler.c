#include "signal_handler.h"
#include "utils.h"
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

timer_t timer;

void set_timer()
{
    struct sigevent signal_event = {
        .sigev_notify = SIGEV_THREAD,
        .sigev_notify_function = invalidate,
        .sigev_notify_attributes = NULL,
        .sigev_value.sival_ptr = &timer
    };

    timer_create(CLOCK_REALTIME, &signal_event, &timer);

    struct itimerspec t = { { 1, 0 }, { 1, 0 } };
    timer_settime(timer, 0, &t, 0);
}

void delete_timer()
{
    timer_delete(timer);
}

void signal_handler(int signal_type) 
{
    switch(signal_type)
    {
        case SIGINT:
            config->keep_running = 0;
            break;
    }
}

void set_sigint_signal() 
{ 
    struct sigaction signal_action;
    memset(&signal_action, 0, sizeof(signal_action));
    signal_action.sa_handler = &signal_handler;
    sigaction(SIGINT, &signal_action, NULL);
}

