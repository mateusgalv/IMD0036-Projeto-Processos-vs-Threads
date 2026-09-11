#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include "ThreadArgs.h"
#include "stepsCount.h"
#include "timer.h"

void *useThread(void *arg) {
    ThreadArgs *args = arg;
    struct timespec timerStart, timerEnd;
    
    // Thread timer start
    clock_gettime(CLOCK_MONOTONIC, &timerStart);
    
    printf(" -> Thread %d - Intervalo [%lld, %lld]\n", args->threadId, args->start, args->end);
    long long steps = 0;
    for(long long i = args->start; i <= args->end; i += args->increment) {
        steps += stepsCount(i);
    }

    printf("Thread %d terminou - Passos = %lld\n", args->threadId, steps);

    // Thread timer end
    clock_gettime(CLOCK_MONOTONIC, &timerEnd);
    args->time = timer(&timerStart, &timerEnd);

    return NULL;
}