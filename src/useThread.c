#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include "ThreadArgs.h"
#include "Timer.h"
#include "stepsCount.h"
#include "elapsedTime.h"

void *useThread(void *arg) {
    ThreadArgs *args = arg;
    Timer threadTime;
    
    // TIMER START
    clock_gettime(CLOCK_MONOTONIC, &threadTime.start);
    
    printf(" --> Thread %d iniciada - Intervalo [%lld, %lld]\n", args->threadId, args->start, args->end);
    long long steps = 0;
    for(long long i = args->start; i <= args->end; i += args->increment) {
        steps += stepsCount(i);
    }
    
    // TIMER END
    clock_gettime(CLOCK_MONOTONIC, &threadTime.end);
    args->time = elapsedTime(&threadTime.start, &threadTime.end);
    printf(" -> Thread %d terminou - Passos = %lld\n | Tempo: %.2e ns\n", args->threadId, steps, (double)args->time);


    return NULL;
}