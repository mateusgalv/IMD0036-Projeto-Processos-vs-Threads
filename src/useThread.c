#define _POSIX_C_SOURCE 199309L

#include <time.h>
#include "ThreadArgs.h"

void *useThread(void *arg) {
    ThreadArgs *args = arg;
    struct timespec timerStart, timerEnd;
    
    clock_gettime(CLOCK_MONOTONIC, &timerStart);
    
    long long steps = 0;
    for(long long i = args->start; i <= args->end; i++) {
        steps += stepsCount(i);
    }

    printf("Thread %d terminou - Passos = %lld\n", args->threadId, steps);

    clock_gettime(CLOCK_MONOTONIC, &timerEnd);
    args->time = timer(&timerStart, &timerEnd);
}