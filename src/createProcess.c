#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "stepsCount.h"
#include "timer.h"
#include "createTempFile.h"

void createProcess(
    int processId,
    long long start,
    long long end,
    int increment
){
    struct timespec timerStart, timerEnd;

    pid_t pid = fork();

    if (pid == 0) {
        // PROCESSO FILHO

        // Process timer start
        clock_gettime(CLOCK_MONOTONIC, &timerStart);

        long long steps = 0;
        for (long long i = start; i <= end; i += increment) {
            steps += stepsCount(i);
        }

        printf("Processo filho %d terminou - Passos = %lld\n", processId, steps);

        // Process timer end
        clock_gettime(CLOCK_MONOTONIC, &timerEnd);
        long long time = timer(&timerStart, &timerEnd);

        createTempFile(processId, steps, time);

        exit(0);
    } else {
        // PROCESSO PAI
        printf(" -> Processo filho %d - Intervalo [%lld, %lld]\n", processId, start, end);
    }

}