//
// Created by aben-ham on 12/22/22.
//

#include "base.h"

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e6) + (time_now.tv_usec);
    return (msecs_time);
}

